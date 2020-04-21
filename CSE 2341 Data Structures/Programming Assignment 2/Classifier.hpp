#ifndef TWEETCLASSIFIER
#define TWEETCLASSIFIER

#include <fstream>
#include <iomanip>
#include <random>
#include <cmath>
#include "DSlib/DSString.hpp"
#include "DSlib/DSVector.hpp"
#include "Tweet.hpp"

struct ScoredWord;

class TweetClassifier{
	private:
		static std::random_device rng;
		double positive_threshhold = 0.0;
		double negative_threshhold = 0.0;
		ScoredWord** wordlist = new ScoredWord*[500000]{nullptr};

		ScoredWord* get_Word(DSString&);
		void increment_score_of(DSString&);
		void decrement_score_of(DSString&);
		double get_score_of(DSString&);
		bool classify(Tweet&);
		void collisions();
	public:
		~TweetClassifier();
		void train(std::istream&, std::istream&);
		void test(std::istream&, std::istream&, const char*);
		ScoredWord* get_word(DSString& word){
			return get_Word(word);
		}
};

struct ScoredWord{
	const DSString word;
	int value = 0;
	bool stopword = false;
	unsigned int positive_count = 0;
	unsigned int negative_count = 0;
	ScoredWord* next_word = nullptr;

	ScoredWord(DSString& string) : word(string){
		if(Tweet::is_stopword(string)) stopword = true;
	}

	~ScoredWord()	{delete next_word;}

	double score()	{
		if(stopword) return double(value) / double(positive_count + negative_count + 1);
		else return 0.0;
	}
};

std::random_device TweetClassifier::rng;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TweetClassifier::~TweetClassifier(){
	for(int i = 0; i < 500000; i++){
		delete wordlist[i];
	}
	delete wordlist;
}

ScoredWord* TweetClassifier::get_Word(DSString& word){
	if(word[0] == '#'){ //homogenize all hashtags into a single entry
		word = '#';
	}
	if(word[0] == '@'){ //homogenize all mentions into a single entry
		word = '@';
	}

	//hash the word to generate its index in the wordlist
	unsigned int hash = word.hash() % 500000;

	//if no ScoredWord exists for this entry, start a new linkedlist of them
	if(wordlist[hash] == nullptr){
		wordlist[hash] = new ScoredWord(word);
		return wordlist[hash];
	}

	//otherwise, iterate down the existing list
	ScoredWord* Word = wordlist[hash];
	while(Word->word != word){
		if(Word->next_word == nullptr){
			Word->next_word = new ScoredWord(word);
		}
		else{
			Word = Word->next_word;
		}
	}
	return Word;
}

void TweetClassifier::increment_score_of(DSString& word){
	ScoredWord* Word = get_Word(word);
	Word->positive_count++;
	Word->value++;
}

void TweetClassifier::decrement_score_of(DSString& word){
	ScoredWord* Word = get_Word(word);
	Word->negative_count++;
	Word->value--;
}

double TweetClassifier::get_score_of(DSString& word){
	return get_Word(word)->score();
}

bool TweetClassifier::classify(Tweet& tweet){
	double tweet_score = 0;
	DSVector<DSString> tweet_words = tweet.get_text().tokenize();
	for(int i = 0; i < tweet_words.len(); i++){
		tweet_score += get_score_of(tweet_words[i]);
	}
	if(tweet_score >= positive_threshhold){
		return true;
	}
	else if(tweet_score < negative_threshhold){
		return false;
	}
	else{
		return rng() % 2;
	}
}

void TweetClassifier::collisions(){
	int total_indices = 500000;
	int indices_used = 0;
	int collision_count = 0;
	int total_words = 0;
	int total_colliding_words = 0;
	for(int i = 0; i < 500000; i++){
		ScoredWord* Word = wordlist[i];
		if(Word != nullptr){
			indices_used++;
			total_words++;
			while(Word->next_word != nullptr){
				collision_count++;
				total_words++;
				total_colliding_words++;
				Word = Word->next_word;
			}
		}
	}
	std::cout << "total_indices\t\t" << total_indices << std::endl;
	std::cout << "indices_used\t\t" << indices_used << std::endl;
	std::cout << "collision_count\t\t" << collision_count << std::endl;
	std::cout << "total_words\t\t" << total_words << std::endl;
	std::cout << "total_colliding_words\t" << total_colliding_words << std::endl;
}

void TweetClassifier::train(std::istream& input, std::istream& target){
	Tweet tweet(input, target);
	for(int i = 0; i < 1000000; i++){
	// while(true){
		tweet = Tweet(input, target);
		tweet.process();
		DSVector<DSString> tweet_words = tweet.get_text().tokenize();
		if(input.eof() || target.eof()){
			break;
		}
		if(tweet.get_sentiment()){
			for(int i = 0; i < tweet_words.len(); i++){
				increment_score_of(tweet_words[i]);
			}
		}
		else{
			for(int i = 0; i < tweet_words.len(); i++){
				decrement_score_of(tweet_words[i]);
			}
		}
	}
	// collisions();
}

void TweetClassifier::test(std::istream& input, std::istream& target, const char* output_filename){
	std::ofstream output(output_filename);
	bool classification;
	char correctness;
	int correct_classifications = 0;
	int incorrect_classifications = 0;
	DSString classified_tweets;
	Tweet tweet(input, target);
	while(tweet.get_text() != ""){
		tweet = Tweet(input, target);
		tweet.process();
		classification = classify(tweet);
		if(tweet.get_text() == ""){
			break;
		}
		if(classification == tweet.get_sentiment()){
			correct_classifications++;
			correctness = 'c';
		}
		else{
			incorrect_classifications++;
			correctness = 'i';
		}
		classified_tweets += tweet.get_id() + ',' + correctness + '\n';
	}
	double accuracy = double(correct_classifications) / double(correct_classifications + incorrect_classifications);
	output << accuracy << '\n' << classified_tweets;	
}

#endif