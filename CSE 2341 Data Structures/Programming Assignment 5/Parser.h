#pragma once
#include <regex>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include "porter2_stemmer.h"
#include "rapidjson/document.h"
#include "DocIndex.h"
#include "IndexInterface.h"

class Parser{
	private:
		// static const std::regex id;				//gnu uses libstdc++ which has a known bug with long
		// static const std::regex id_name;			//regex matches seemingly depleting the stack
		// static const std::regex content;			//https://gcc.gnu.org/bugzilla/show_bug.cgi?id=61582
		// static const std::regex content_name;
		static const std::regex newlines;
		static const std::regex escaped_quotes;
		static const std::regex line_breaks;
		static const std::regex parties;
		static const std::regex h1_tags;
		static const std::regex judge;
		static const std::regex judge_prefix;
		static const std::regex html;
		static const std::regex alpha_filter;
		static const std::regex whitespace;
		static const std::regex stopwords;
		std::smatch matches;
		rapidjson::Document json;

		std::vector<std::string> tokenize(std::string);
	public:
		std::string stemQuery();
		Document parseDocument(std::ifstream& doc_file);
		void indexDocument(std::ifstream& doc_file, IndexInterface& index);
};