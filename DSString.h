//
// Created by Caleb Moore on 2/3/21.
//

#ifndef INC_21S_PA02_DSSTRING_H
#define INC_21S_PA02_DSSTRING_H
#include <iostream>
#include <cstring>
#include <cmath>

class DSString{

private:
    //private variable(s)
    char* word;


public:

    //constructors and destructors
    DSString();
    DSString(const char*);
    DSString(const DSString&);
    ~DSString();

    //assignment and + operator overload declaration
    DSString& operator= (const char*);
    DSString& operator= (const char);
    DSString& operator= (const DSString&);
    DSString operator+ (const DSString&);
    DSString operator+ (const char*&);

    // comparison operators and []
    bool operator== (const DSString&) const;
    bool operator== (const char*&) const;
    bool operator> (const DSString&) const;
    bool operator< (const DSString&) const;
    char& operator[] (const int);

    //returns the length of a DSString object
    int getLength();

    //used to find a substring of a DSString
    DSString substring(int start, int numChars);

    //used to get the char* of a DSString
    char* c_str();

    //used to output DSString type objects
    friend std::ostream& operator<< (std::ostream&, const DSString&);

    //used to make a DSString of lower case letters
    void lower();

    //check for number or make number
    bool is_digit(const int& c);
    int to_digit();


};


#endif
