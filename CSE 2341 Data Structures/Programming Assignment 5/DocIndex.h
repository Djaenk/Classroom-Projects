#pragma once
#include <string>
#include <vector>

struct Document{
	int id = 0;
	std::string parties = "";
	std::string judge = "";
	std::string date = "";
	std::string excerpt = "";
	int term_count = 0;

	bool operator==	(const Document& comparand)		{return id == comparand.id;}
	bool operator!=	(const Document& comparand)		{return id != comparand.id;}
};

struct DocIndex{
	std::string word = "";
	std::vector<int> doc_indices;
	std::vector<int> frequencies;

	DocIndex() = default;
	DocIndex(const std::string& word) : word(word) {}
	DocIndex(const DocIndex& word){
		this->word = word.word;
		this->doc_indices = word.doc_indices;
		this->frequencies = word.frequencies;
	}
	bool operator==	(const DocIndex& comparand)		{return word == comparand.word;}
	bool operator==	(const std::string& comparand)	{return word == comparand;}
	bool operator!=	(const DocIndex& comparand)		{return word != comparand.word;}
	bool operator!= (const std::string& comparand)	{return word != comparand;}
	bool operator<	(const DocIndex& comparand)		{return word < comparand.word;}
	bool operator<	(const std::string& comparand)	{return word < comparand;}
	bool operator>	(const DocIndex& comparand)		{return word > comparand.word;}
	bool operator>	(const std::string& comparand)	{return word > comparand;}
	void increment(const int doc_index){
		for(int i = 0; i < doc_indices.size(); i++){
			if(doc_indices[i] == doc_index){
				frequencies[i]++;
				return;
			}
		}
		doc_indices.push_back(doc_index);
		frequencies.push_back(1);
	}
	int total_frequency(){
		int total = 0;
		for(int i = 0; i < frequencies.size(); i++)
			total += frequencies[i];
		return total;
	}
};