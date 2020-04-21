#ifndef TWEET
#define TWEET

#include <regex>
#include <algorithm>

class Tweet{
	private:
		std::string row;
		std::string id;
		std::string username;
		std::string text;
		bool sentiment = false;

		std::string classification;
		std::regex parser = std::regex("(@[\\w_-]+)|#|(&.+?;)|([^'\\w\\d\\s])|(\\d)|(\\S+\\.((com)|(net)|(org)|(.edu)|(.gov))[\\w\\d/]*)");
		std::regex stop_words = std::regex("(^|\\s)((a)|(about)|(above)|(after)|(again)|(against)|(all)|(am)|(an)|(and)|(any)|(are)|(aren't)|(as)|(at)|(be)|(because)|(been)|(before)|(being)|(below)|(between)|(both)|(but)|(by)|(can't)|(cannot)|(could)|(couldn't)|(did)|(didn't)|(do)|(does)|(doesn't)|(doing)|(don't)|(down)|(during)|(each)|(few)|(for)|(from)|(further)|(had)|(hadn't)|(has)|(hasn't)|(have)|(haven't)|(having)|(he)|(he'd)|(he'll)|(he's)|(her)|(here)|(here's)|(hers)|(herself)|(him)|(himself)|(his)|(how)|(how's)|(i)|(i'd)|(i'll)|(i'm)|(i've)|(if)|(in)|(into)|(is)|(isn't)|(it)|(it's)|(its)|(itself)|(let's)|(me)|(more)|(most)|(mustn't)|(my)|(myself)|(no)|(nor)|(not)|(of)|(off)|(on)|(once)|(only)|(or)|(other)|(ought)|(our)|(ours)|(ourselves)|(out)|(over)|(own)|(same)|(shan't)|(she)|(she'd)|(she'll)|(she's)|(should)|(shouldn't)|(so)|(some)|(such)|(than)|(that)|(that's)|(the)|(their)|(theirs)|(them)|(themselves)|(then)|(there)|(there's)|(these)|(they)|(they'd)|(they'll)|(they're)|(they've)|(this)|(those)|(through)|(to)|(too)|(under)|(until)|(up)|(very)|(was)|(wasn't)|(we)|(we'd)|(we'll)|(we're)|(we've)|(were)|(weren't)|(what)|(what's)|(when)|(when's)|(where)|(where's)|(which)|(while)|(who)|(who's)|(whom)|(why)|(why's)|(with)|(won't)|(would)|(wouldn't)|(you)|(you'd)|(you'll)|(you're)|(you've)|(your)|(yours)|(yourself)|(yourselves))(?=^|\\s)");
		std::regex extra_whitespace = std::regex("\\s{2,}");
		std::regex leading_whitespace = std::regex("^\\s");
		std::string positive = "4";
		std::string negative = "0";


	public:
		Tweet(const std::string&, const std::string&, const std::string&, const std::string&);
		Tweet(std::istream&, std::istream&);

		std::string get_row()			{return row;}
		std::string get_id()			{return id;}
		std::string get_username()		{return username;}
		std::string get_text()			{return text;}
		void set_sentiment(bool sentiment)	{this->sentiment = sentiment;}
		bool get_sentiment()		{return sentiment;}
		void process();
		bool is_stopword(std::string&);
		std::string to_string();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Tweet::Tweet(const std::string& row, const std::string& id, const std::string& username, const std::string& text){
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
	std::transform(text.begin(), text.end(), text.begin(), ::toupper);
	text = std::regex_replace(text.c_str(), parser, " ").c_str();
};

bool Tweet::is_stopword(std::string& word){
	return std::regex_match(word.c_str(), stop_words);
}

std::string Tweet::to_string(){
	return row + ',' + id + ',' + username + ',' + text;
}

#endif