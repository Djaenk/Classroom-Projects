#include "IndexInterface.h"

int AVLTreeIndex::docs_length(){
	return docs.size();
}

int AVLTreeIndex::size(){
	return index.size();
}

void AVLTreeIndex::clear(){
	index.clear();
}

void AVLTreeIndex::addDocument(const Document doc){
	docs.push_back(doc);
}

void AVLTreeIndex::incrementWord(std::string word, const Document doc){
	for(int i = 0; i < docs.size(); i++){
		if(docs[i] == doc){
			DocIndex new_word = DocIndex(word);
			index[new_word].increment(i);
		}
	}
}

void AVLTreeIndex::incrementWord(std::string word, const int doc_index){
	DocIndex new_word = DocIndex(word);
	index[new_word].increment(doc_index);
}

DocIndex& AVLTreeIndex::operator[](std::string word){
	DocIndex new_word = DocIndex(word);
	return index[new_word];
}

DocIndex& AVLTreeIndex::operator[](DocIndex word){
	return index[word];
}