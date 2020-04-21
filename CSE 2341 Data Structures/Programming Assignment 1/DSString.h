#ifndef DSSTRING
#define DSSTRING

#include <iostream>
#include <cstring>

class DSString{

    private:
<<<<<<< HEAD
<<<<<<< HEAD
    	char* data = nullptr;
=======
        char* data = nullptr;
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
        char* data = nullptr;
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec

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
        bool operator== (const DSString&);
        bool operator< (const char*);
        bool operator< (const DSString&);
        char& operator[] (const int);

        int size();

      //substring: parameter a represents the starting position
      //parameter b represents the number of characters to copy
      //into the substring that is returned.  If b is positive,
      //count forward from position a.  If b is negative, count
      //backward from position a.
        DSString substring(int a, int b);

      //c_str returns a c-string representation of the DSString obj.
        char* c_str();

        friend std::ostream& operator<< (std::ostream&, const DSString&);
        friend std::istream& operator>> (std::istream&, DSString&);
};

std::istream& getline(std::istream&, DSString&);

#endif
