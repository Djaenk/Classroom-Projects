#pragma once
#include "Parser.h"
#include "DocIndex.h"
#include "IndexInterface.h"
#include <experimental/filesystem>
#include <filesystem>
#include <iostream>

class SearchEngine{
	private:
		AVLTreeIndex index;
		Parser parser;
		
		DocIndex& getWord(const std::string);
		DocIndex& getWord(const char*);
	public:
		void parseDirectory(const std::string);
		void wordQuery();
};