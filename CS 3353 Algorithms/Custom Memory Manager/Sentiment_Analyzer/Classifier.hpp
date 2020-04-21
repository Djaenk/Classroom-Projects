#ifndef TWEETCLASSIFIER
#define TWEETCLASSIFIER

#include <fstream>
#include <iomanip>
#include <random>
#include <cmath>
#include <regex>
#include <string>
#include <vector>
#include "Tweet.hpp"

struct ScoredWord;

class TweetClassifier{
	private:
		std::random_device rng;
		double positive_threshhold = 0.0;
		double negative_threshhold = 0.0;
		ScoredWord** wordlist = new ScoredWord*[500000]{nullptr};

		ScoredWord* get_Word(std::string&);
		void increment_score_of(std::string&);
		void decrement_score_of(std::string&);
		double get_score_of(std::string&);
		bool classify(Tweet&);
		void collisions();
	public:
		~TweetClassifier();
		void train(std::istream&, std::istream&, uint);
		void test(std::istream&, std::istream&, const char*, uint);
		ScoredWord* get_word(std::string& word){
			return get_Word(word);
		}
};

struct ScoredWord{
	const std::string word;
	int value = 0;
	bool stopword = false;
	unsigned int positive_count = 0;
	unsigned int negative_count = 0;
	ScoredWord* next_word = nullptr;
	std::regex stop_words = std::regex("(^|\\s)((a)|(about)|(above)|(after)|(again)|(against)|(all)|(am)|(an)|(and)|(any)|(are)|(aren't)|(as)|(at)|(be)|(because)|(been)|(before)|(being)|(below)|(between)|(both)|(but)|(by)|(can't)|(cannot)|(could)|(couldn't)|(did)|(didn't)|(do)|(does)|(doesn't)|(doing)|(don't)|(down)|(during)|(each)|(few)|(for)|(from)|(further)|(had)|(hadn't)|(has)|(hasn't)|(have)|(haven't)|(having)|(he)|(he'd)|(he'll)|(he's)|(her)|(here)|(here's)|(hers)|(herself)|(him)|(himself)|(his)|(how)|(how's)|(i)|(i'd)|(i'll)|(i'm)|(i've)|(if)|(in)|(into)|(is)|(isn't)|(it)|(it's)|(its)|(itself)|(let's)|(me)|(more)|(most)|(mustn't)|(my)|(myself)|(no)|(nor)|(not)|(of)|(off)|(on)|(once)|(only)|(or)|(other)|(ought)|(our)|(ours)|(ourselves)|(out)|(over)|(own)|(same)|(shan't)|(she)|(she'd)|(she'll)|(she's)|(should)|(shouldn't)|(so)|(some)|(such)|(than)|(that)|(that's)|(the)|(their)|(theirs)|(them)|(themselves)|(then)|(there)|(there's)|(these)|(they)|(they'd)|(they'll)|(they're)|(they've)|(this)|(those)|(through)|(to)|(too)|(under)|(until)|(up)|(very)|(was)|(wasn't)|(we)|(we'd)|(we'll)|(we're)|(we've)|(were)|(weren't)|(what)|(what's)|(when)|(when's)|(where)|(where's)|(which)|(while)|(who)|(who's)|(whom)|(why)|(why's)|(with)|(won't)|(would)|(wouldn't)|(you)|(you'd)|(you'll)|(you're)|(you've)|(your)|(yours)|(yourself)|(yourselves))(?=^|\\s)");

	ScoredWord(std::string& string) : word(string){
		if(std::regex_match(string.c_str(), stop_words)) stopword = true;
	}

	~ScoredWord()	{delete next_word;}

	double score()	{
		if(stopword) return double(value) / double(positive_count + negative_count + 1);
		else return 0.0;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TweetClassifier::~TweetClassifier(){
	for(int i = 0; i < 500000; i++){
		delete wordlist[i];
	}
	delete wordlist;
}

ScoredWord* TweetClassifier::get_Word(std::string& word){
	if(word[0] == '#'){ //homogenize all hashtags into a single entry
		word = '#';
	}
	if(word[0] == '@'){ //homogenize all mentions into a single entry
		word = '@';
	}

	//hash the word to generate its index in the wordlist
	unsigned int hash;
	for(unsigned int i = 0; i < word.length(); i++){
		hash = (hash * 33) ^ word[i];
	}
	hash %= 500000;

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

void TweetClassifier::increment_score_of(std::string& word){
	ScoredWord* Word = get_Word(word);
	Word->positive_count++;
	Word->value++;
}

void TweetClassifier::decrement_score_of(std::string& word){
	ScoredWord* Word = get_Word(word);
	Word->negative_count++;
	Word->value--;
}

double TweetClassifier::get_score_of(std::string& word){
	return get_Word(word)->score();
}

bool TweetClassifier::classify(Tweet& tweet){
	double tweet_score = 0;
	std::vector<std::string> tweet_words;
	std::istringstream ss(tweet.get_text());
	std::string token;
	while(std::getline(ss, token, ' ')){
		tweet_words.push_back(token);
	}
	for(size_t i = 0; i < tweet_words.size(); i++){
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

void TweetClassifier::train(std::istream& input, std::istream& target, uint size){
	Tweet tweet(input, target);
	for(uint i = 0; i < size; ++i){
		tweet = Tweet(input, target);
		tweet.process();
		std::vector<std::string> tweet_words;
		std::istringstream ss(tweet.get_text());
		std::string token;
		while(std::getline(ss, token, ' ')){
			tweet_words.push_back(token);
		}
		if(input.eof() || target.eof()){
			break;
		}
		if(tweet.get_sentiment()){
			for(size_t i = 0; i < tweet_words.size(); i++){
				increment_score_of(tweet_words[i]);
			}
		}
		else{
			for(size_t i = 0; i < tweet_words.size(); i++){
				decrement_score_of(tweet_words[i]);
			}
		}
	}
	// collisions();
}

void TweetClassifier::test(std::istream& input, std::istream& target, const char* output_filename, uint size){
	std::ofstream output(output_filename);
	bool classification;
	char correctness;
	int correct_classifications = 0;
	int incorrect_classifications = 0;
	std::string classified_tweets;
	Tweet tweet(input, target);
	for(uint i = 0; i < size; ++i){
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