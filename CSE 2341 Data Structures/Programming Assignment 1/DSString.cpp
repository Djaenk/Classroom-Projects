#include "DSString.h"

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
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
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
=======
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
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
    char* new_string = new char[strlen(data) + 2];
    strcpy(new_string, data);
    new_string[strlen(data)] = character;
    new_string[strlen(data) + 1] = '\0';
    DSString new_String = DSString(new_string);
    delete[] new_string;
    return new_String;
<<<<<<< HEAD
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
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
<<<<<<< HEAD
<<<<<<< HEAD
	char* temp = data;
	int length = strlen(data);
	data = new char[strlen(data) + 2];
	strcpy(data, temp);
	data[length] = character;
	data[length + 1] = '\0';
	delete[] temp;
	return *this;
=======
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
    char* temp = data;
    int length = strlen(data);
    data = new char[strlen(data) + 2];
    strcpy(data, temp);
    data[length] = character;
    data[length + 1] = '\0';
    delete[] temp;
    return *this;
<<<<<<< HEAD
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
}

bool DSString::operator==(const char* string){
    if(strcmp(string, data) == 0){
        return true;
    }
    else{
        return false;
    }
}

bool DSString::operator==(const DSString& String){
    if(strcmp(String.data, data) == 0){
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
    return DSString(string);
}

char* DSString::c_str(){
    char* string = new char[strlen(data)];
    strcpy(string, data);
    return string;
}

std::ostream& operator<<(std::ostream& stream, const DSString& String){
    return stream << String.data;
}

std::istream& operator>>(std::istream& stream, DSString& String){
    String = DSString();
    char character;
    while(isspace(stream.peek())){ //ignore initial whitespace
        stream.ignore();
    }
    while(character = stream.get()){
        if(isspace(character)){
            break;
        }
        String += DSString(character);
    }
    return stream;
}

std::istream& getline(std::istream& stream, DSString& String){
    char buffer[151]; //buffer to hold c-string read from the stream before converting it to a DSString
    stream.getline(buffer, 150);
    String = buffer;
    return stream;
}
