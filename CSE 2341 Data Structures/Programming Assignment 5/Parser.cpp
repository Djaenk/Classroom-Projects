#include "Parser.h"
#include <iostream>

using namespace std::regex_constants;
// const std::regex Parser::id				= std::regex("\"id\": \\w*?(?=,)");
// const std::regex Parser::id_name		= std::regex("\"id\": ");
// // const std::regex Parser::content		= std::regex("(?<=\"html_with_citations\": \").*?(?=\",\\n)"); //C++ implements ECMAScript, does not support lookbehind
// const std::regex Parser::content		= std::regex("\"html_with_citations\": \".*\",\\n", optimize);
// const std::regex Parser::content_name	= std::regex("\"html_with_citations\": \"", optimize);
const std::regex Parser::newlines		= std::regex("\\n", optimize);
const std::regex Parser::escaped_quotes	= std::regex("\\\\\"", optimize);
const std::regex Parser::line_breaks	= std::regex("<br>", optimize);
const std::regex Parser::parties		= std::regex("<h1>(.|\\n|\\r)*?</h1>", optimize);
const std::regex Parser::h1_tags		= std::regex("</?h1>", optimize);
const std::regex Parser::judge			= std::regex("JUSTICE [^\\d\\s]*(?= delivered the opinion)", icase | optimize);
const std::regex Parser::judge_prefix	= std::regex(">");
const std::regex Parser::html			= std::regex("(<.*?>)|(&.{0,10};)", optimize);
const std::regex Parser::alpha_filter	= std::regex("[^a-zA-Z ]", optimize);
const std::regex Parser::whitespace		= std::regex("\\s{2,}");
const std::regex Parser::stopwords		= std::regex("you|him|his|self|she|shes|her|hers|its|they|them|their|theirs|themselves|what|which|who|whom|this|that|thatll|these|those|are|was|were|been|being|have|has|had|having|does|did|doing|the|and|but|because|until|while|for|with|about|against|between|into|through|during|before|after|above|below|from|down|out|off|over|under|again|further|then|once|here|there|when|where|why|how|all|any|both|each|few|more|most|other|some|such|nor|not|only|own|same|than|too|very|can|will|just|dont|should|now|ain|arent|couldnt|didnt|doesnt|hadnt|hasnt|havent|isnt|mightnt|mustnt|neednt|shant|shouldnt|wasnt|werent|wont|would", icase | optimize);

Document Parser::parseDocument(std::ifstream& doc_file){
	std::string buffer;
	doc_file.seekg(0, std::ios::end);
    buffer.resize(doc_file.tellg());
    doc_file.seekg(0, std::ios::beg);
    doc_file.read(&buffer[0], buffer.size());
    doc_file.close();

	json.Parse(buffer.c_str());
	Document doc;
	doc.id = json["id"].GetInt();
	std::string content = json["html_with_citations"].GetString();
	std::regex_search(content, matches, parties);
	if(matches.size() > 0)
		doc.parties = std::regex_replace(std::string(matches[0]), html, "");
	std::regex_search(content, matches, judge);
	if(matches.size() > 0)
		doc.judge = matches[0];
	content = std::regex_replace(content, html,"");
	doc.excerpt = content.substr(0,2000);
	content = std::regex_replace(content, alpha_filter, "");
	std::cout << content << std::endl;
	return doc;
}

void Parser::indexDocument(std::ifstream& doc_file, IndexInterface& index){
	std::string buffer;
	doc_file.seekg(0, std::ios::end);
    buffer.resize(doc_file.tellg());
    doc_file.seekg(0, std::ios::beg);
    doc_file.read(&buffer[0], buffer.size());
    doc_file.close();

	json.Parse(buffer.c_str());
	Document doc;
	doc.id = json["id"].GetInt();
	std::string content = json["html_with_citations"].GetString();
	std::regex_search(content, matches, parties);
	if(matches.size() > 0)
		doc.parties = std::regex_replace(std::string(matches[0]), html, "");
	std::regex_search(content, matches, judge);
	if(matches.size() > 0)
		doc.judge = matches[0];
	content = std::regex_replace(content, html, " ");
	doc.excerpt = content.substr(0,2000);
	// content = std::regex_replace(content, alpha_filter, "");
	index.addDocument(doc);

	auto lastpos = content.find_first_not_of(' ', 0);
	auto pos = content.find_first_of(' ', lastpos);
	std::string token;
	while(pos != std::string::npos || lastpos != lastpos){
		token = content.substr(lastpos, pos - lastpos);
		lastpos = content.find_first_not_of(' ', pos);
		pos = content.find_first_of(' ', lastpos);
		if(token.length() < 2){continue;}
		// if(std::regex_search(token, stopwords)) continue;
		Porter2Stemmer::trim(token);
		Porter2Stemmer::stem(token);
		if(token.length() > 1)
			index.incrementWord(token, index.docs_length() - 1);
	}
}