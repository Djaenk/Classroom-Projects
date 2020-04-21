#ifndef TWEET
#define TWEET

#include "DSlib/DSString.hpp"
#include <regex>

class Tweet{
	private:
		DSString row;
		DSString id;
		DSString username;
		DSString text;
		bool sentiment = false;

		DSString classification;
		static const DSString positive;
		static const DSString negative;

		static const std::regex parser;
		static const std::regex stop_words;
		static const std::regex extra_whitespace;
		static const std::regex leading_whitespace;

	public:
		Tweet(const DSString&, const DSString&, const DSString&, const DSString&);
		Tweet(std::istream&, std::istream&);

		DSString get_row()			{return row;}
		DSString get_id()			{return id;}
		DSString get_username()		{return username;}
		DSString get_text()			{return text;}
		void set_sentiment(bool sentiment)	{this->sentiment = sentiment;}
		bool get_sentiment()		{return sentiment;}
		void process();
		static bool is_stopword(DSString&);
		DSString to_string();
};

const std::regex Tweet::parser = std::regex("(@[\\w_-]+)|#|(&.+?;)|([^'\\w\\d\\s])|(\\d)|(\\S+\\.((com)|(net)|(org)|(.edu)|(.gov))[\\w\\d/]*)");
const std::regex Tweet::stop_words = std::regex("(^|\\s)((a)|(about)|(above)|(after)|(again)|(against)|(all)|(am)|(an)|(and)|(any)|(are)|(aren't)|(as)|(at)|(be)|(because)|(been)|(before)|(being)|(below)|(between)|(both)|(but)|(by)|(can't)|(cannot)|(could)|(couldn't)|(did)|(didn't)|(do)|(does)|(doesn't)|(doing)|(don't)|(down)|(during)|(each)|(few)|(for)|(from)|(further)|(had)|(hadn't)|(has)|(hasn't)|(have)|(haven't)|(having)|(he)|(he'd)|(he'll)|(he's)|(her)|(here)|(here's)|(hers)|(herself)|(him)|(himself)|(his)|(how)|(how's)|(i)|(i'd)|(i'll)|(i'm)|(i've)|(if)|(in)|(into)|(is)|(isn't)|(it)|(it's)|(its)|(itself)|(let's)|(me)|(more)|(most)|(mustn't)|(my)|(myself)|(no)|(nor)|(not)|(of)|(off)|(on)|(once)|(only)|(or)|(other)|(ought)|(our)|(ours)|(ourselves)|(out)|(over)|(own)|(same)|(shan't)|(she)|(she'd)|(she'll)|(she's)|(should)|(shouldn't)|(so)|(some)|(such)|(than)|(that)|(that's)|(the)|(their)|(theirs)|(them)|(themselves)|(then)|(there)|(there's)|(these)|(they)|(they'd)|(they'll)|(they're)|(they've)|(this)|(those)|(through)|(to)|(too)|(under)|(until)|(up)|(very)|(was)|(wasn't)|(we)|(we'd)|(we'll)|(we're)|(we've)|(were)|(weren't)|(what)|(what's)|(when)|(when's)|(where)|(where's)|(which)|(while)|(who)|(who's)|(whom)|(why)|(why's)|(with)|(won't)|(would)|(wouldn't)|(you)|(you'd)|(you'll)|(you're)|(you've)|(your)|(yours)|(yourself)|(yourselves))(?=^|\\s)");
const std::regex Tweet::extra_whitespace = std::regex("\\s{2,}");
const std::regex Tweet::leading_whitespace = std::regex("^\\s");
const DSString Tweet::positive = DSString('4');
const DSString Tweet::negative = DSString('0');

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Tweet::Tweet(const DSString& row, const DSString& id, const DSString& username, const DSString& text){
	this->row = row;
	this->id = id;
	this->username = username;
	this->text = text;
}

Tweet::Tweet(std::istream& input, std::istream& target){
	getline(input, row, ',');
	getline(input, id, ',');
	getline(input, username, ',');
	getline(input, text);
	getline(target, row, ',');
	getline(target, classification, ',');
	getline(target, id);
	if(classification == positive){
		sentiment = true;
	}
	else{
		sentiment = false;
	}
}

void Tweet::process(){
	//constructing all these regex objects every time I preprocessed a tweet was nuking my runtime.
	//I switched to combining as many of them into a single expression as possible and made them
	//static const member variable to minimize the number of instantiations.

	// std::regex articles(" .{1,2} "); //I'm just assuming all words consisting of one or two letters are useless
	// std::regex entities("&.+?;");
	// std::regex handles("(@[\\w_-]+)");
	// std::regex hashtags("((^|\s)#.*?(?=\s))");
	// std::regex links("\\S+\\.((com)|(net)|(org)|(.edu)|(.gov))[\\w\\d/]*");
	// std::regex punctuation("[^\\w\\d\\s]");
	// std::regex numbers("\\d");
	// std::regex extra_whitespace("\\s{2,}");
	// std::regex leading_whitespace("^\\s");
	text.to_lowercase();
	text = std::regex_replace(text.c_str(), parser, " ").c_str();
};

bool Tweet::is_stopword(DSString& word){
	return std::regex_match(word.c_str(), stop_words);
}

DSString Tweet::to_string(){
	return row + ',' + id + ',' + username + ',' + text;
}

#endif