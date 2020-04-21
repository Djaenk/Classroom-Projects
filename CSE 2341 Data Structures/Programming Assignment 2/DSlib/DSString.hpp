#ifndef DSSTRING
#define DSSTRING

#include <iostream>
#include <cstring>
#include "DSVector.hpp"

class DSString{

    private:
    	char* data = nullptr;
        static char buffer[1121]; //DSString instances share a buffer to save on memory and allocation

    public:
        DSString();
		DSString(const char&);
        DSString(const char*);
        DSString(const DSString&);
       ~DSString();

        DSString& operator= (const char*);
        DSString& operator= (const DSString&);
        DSString operator+ (const DSString&);
		DSString operator+ (const char&);
        DSString& operator+= (const DSString&);
		DSString& operator+= (const char&);
        bool operator== (const char*);
        bool operator== (const DSString&) const;
		bool operator!= (const char*);
		bool operator!= (const DSString&) const;
        bool operator< (const char*);
        bool operator< (const DSString&);
        char& operator[] (const int);

        int size();
		DSString substring(int a, int b);
		void to_lowercase();
		unsigned int hash(); //based on xor dbj2 variant
		DSVector<DSString> tokenize();

        char* c_str();

        friend std::ostream& operator<< (std::ostream&, const DSString&);
		friend std::istream& operator>> (std::istream&, DSString&);
        friend std::istream& getline(std::istream&, DSString&);
        friend std::istream& getline(std::istream&, DSString&, char);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char DSString::buffer[1121] = {};

DSString::DSString(){
	data = new char[1];
	data[0] = '\0';
}

DSString::DSString(const char& character){
	data = new char[2];
	data[0] = character;
	data[1] = '\0';
}

DSString::DSString(const char* string){
	data = new char[strlen(string) + 1];
	strcpy(data, string);
}

DSString::DSString(const DSString& String){
	data = new char[strlen(String.data) + 1];
	strcpy(data, String.data);
}

DSString::~DSString(){
	delete[] data;
	data = nullptr;
}

DSString& DSString::operator=(const char* string){
	delete[] data;
	data = new char[strlen(string) + 1];
	strcpy(data, string);
	return *this;
}

DSString& DSString::operator=(const DSString& String){
	delete[] data;
	data = new char[strlen(String.data) + 1];
	strcpy(data, String.data);
	return *this;
}

DSString DSString::operator+(const DSString& String){
	char* new_string = new char[strlen(data) + strlen(String.data) + 1];
	strcpy(new_string, data);
	strcat(new_string, String.data);
	DSString new_String = DSString(new_string);
	delete[] new_string;
	return new_String;
}

DSString DSString::operator+(const char& character){
	char* new_string = new char[strlen(data) + 2];
	strcpy(new_string, data);
	new_string[strlen(data)] = character;
	new_string[strlen(data) + 1] = '\0';
	DSString new_String = DSString(new_string);
	delete[] new_string;
	return new_String;
}

DSString& DSString::operator+=(const DSString& String){
	char* temp = data;
	data = new char[strlen(data) + strlen(String.data) + 1];
	strcpy(data, temp);
	strcat(data, String.data);
	delete[] temp;
	return *this;
}

DSString& DSString::operator+=(const char& character){
	char* temp = data;
	int length = strlen(data);
	data = new char[strlen(data) + 2];
	strcpy(data, temp);
	data[length] = character;
	data[length + 1] = '\0';
	delete[] temp;
	return *this;
}

bool DSString::operator==(const char* string){
	if(strcmp(string, data) == 0){
		return true;
	}
	else{
		return false;
	}
}

bool DSString::operator==(const DSString& String) const{
	if(strcmp(String.data, data) == 0){
		return true;
	}
	else{
		return false;
	}
}

bool DSString::operator!=(const char* string){
	if(strcmp(string, data) != 0){
		return true;
	}
	else{
		return false;
	}
}

bool DSString::operator!=(const DSString& String) const{
	if(strcmp(String.data, data) != 0){
		return true;
	}
	else{
		return false;
	}
}

bool DSString::operator<(const char* string){
	if(strcmp(string, data) < 0){
		return true;
	}
	else{
		return false;
	}
}

bool DSString::operator<(const DSString& String){
	if(strcmp(String.data, data) < 0){
		return true;
	}
	else{
		return false;
	}
}

char& DSString::operator[](const int index){
	return data[index];
}

int DSString::size(){
	return strlen(data);
}

void DSString::to_lowercase(){
	for(unsigned int i = 0; i < strlen(data); i++){
		data[i] = tolower(data[i]);
	}
}

unsigned int DSString::hash(){
	unsigned int len = strlen(data);
	unsigned int hash = 5381;
	for(unsigned int i = 0; i < len; i++){
		hash = (hash * 33) ^ data[i];
	}
	return hash;
}

DSVector<DSString> DSString::tokenize(){
	char* copy = new char[strlen(data) + 1];
	strcpy(copy, data);
	DSVector<DSString> tokens;
	char* token = strtok(copy, " ");
	while(token != NULL){
		tokens.push_back(DSString(token));
		token = strtok(NULL, " ");
	}
	delete[] copy;
	return tokens;
}

DSString DSString::substring(int a, int b){
	char* string = new char[b];
	if(b >= 0){
		for(int i = 0; i < b; i++){
			string[i] = data[a + i];
		}
	}
	if(b < 0){
		for(int i = 0; i > b; i--){
			string[i] = data[a - b - i];
		}
	}
	DSString substring = DSString(string);
	delete[] string;
	return substring;
}

char* DSString::c_str(){
	return data;
}

std::ostream& operator<<(std::ostream& stream, const DSString& String){
	return stream << String.data;
}

std::istream& operator>>(std::istream& stream, DSString& String){
	char character;
	while(isspace(stream.peek())){ //ignore initial whitespace
		stream.ignore();
	}
	for(int i = 0; character = stream.get(); i++){
		if(isspace(character)){
			break;
		}
		DSString::buffer[i] = character;
	}
	String = DSString::buffer;
	return stream;
}

std::istream& getline(std::istream& stream, DSString& String){
	stream.getline(DSString::buffer, 1120);
	String = DSString::buffer;
	return stream;
}

std::istream& getline(std::istream& stream, DSString& String, char delimiter){
	stream.getline(DSString::buffer, 1120, delimiter);
	String = DSString::buffer;
	return stream;
}

#endif