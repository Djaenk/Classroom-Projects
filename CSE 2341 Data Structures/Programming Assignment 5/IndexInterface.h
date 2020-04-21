#pragma once
#include <string>
#include <vector>
#include "DocIndex.h"
#include "avltree.h"

class IndexInterface{
	public:
		virtual ~IndexInterface() {}

		virtual int docs_length() = 0;
		virtual int size() = 0;
		virtual void clear() = 0;
		virtual void addDocument(const Document) = 0;
		virtual void incrementWord(const std::string, const Document) = 0;
		virtual void incrementWord(const std::string, const int) = 0;
		virtual DocIndex& operator[](std::string) = 0;
		virtual DocIndex& operator[](DocIndex) = 0;

		// virtual void saveToDisk(std::experimental::filesystem::path) = 0;
		// virtual void loadFromDisk(std::experimental::filesystem::path) = 0;
};

class AVLTreeIndex : public IndexInterface{
	private:
		std::vector<Document> docs;
		AVLNode<DocIndex> index;
	public:
		int docs_length();
		int size();
		void clear();
		void addDocument(const Document);
		void incrementWord(const std::string, const Document);
		void incrementWord(const std::string, const int);
		DocIndex& operator[](const std::string);
		DocIndex& operator[](const DocIndex);

		// void saveToDisk(std::experimental::filesystem::path);
		// void loadFromDisk(std::experimental::filesystem::path);

};

class HashTableIndex : public IndexInterface{
	private:
		std::vector<Document> docs;
		// HashTable<std::string, DocIndex> index;
	public:
		int length();
		void clear();
		void incrementWord(const std::string, const Document);
		DocIndex& operator[](std::string);
		DocIndex& operator[](DocIndex);

		// void saveToDisk(std::experimental::filesystem::path);
		// void loadFromDisk(std::experimental::filesystem::path);
};