//
// Created by Caleb Moore on 2/3/21.
//

#include "DSString.h"
//*****GO TO .h FILE FOR COMMENTS ABOUT FUNCTIONS******

DSString::DSString(const DSString& m) {
    word = new char[strlen(m.word) + 1];
    strcpy(word, m.word);
}

DSString::DSString(){
    word = nullptr;
}

DSString::DSString(const char * s){
    word = new char[strlen(s) + 1];
    strcpy(word, s);
}

DSString& DSString::operator=(const DSString& c){
    if(word != nullptr){
        delete[] word;
    }
    word = new char[strlen(c.word) + 1];
    strcpy(word, c.word);
    return *this;
}

DSString::~DSString(){
    if(word != nullptr){
        delete[] word;
    }
}

DSString &DSString::operator=(const char * c){
    if(word != nullptr){
        delete[] word;
    }
    word = new char[strlen(c) + 1];
    strcpy(word, c);
    return *this;
}
DSString DSString::operator+(const DSString & n){
    char* temp = new char[strlen(word) + strlen(n.word) + 1];
    DSString temp1 (temp);
    strcat(temp1.word, word);
    strcat(temp1.word, n.word);
    delete[] temp;
    return temp1;
}

std::ostream &operator<<(std::ostream & output, const DSString & s){
    output << s.word;
    return output;
}

bool DSString::operator==(const DSString & s) const{
    if(strcmp(word, s.word) == 0){
        return true;
    }
    return false;
}

int DSString::getLength(){
    return strlen(word);
}

bool DSString::operator>(const DSString & s) const{
    if(strcmp(word, s.word) > 0){
        return true;
    }
    return false;
}

bool DSString::operator<(const DSString & s) const{
    if(strcmp(word, s.word) < 0){
        return true;
    }
    return false;
}

char &DSString::operator[](const int p){
    if(p >= getLength() || p < 0){
        throw std::out_of_range("bad string location access");
    }
    return word[p];
}

char* DSString::c_str(){
    return word;
}

//I found help for this one on a stack overflow page on duplicating char*
DSString DSString::substring(int start, int numChars){
    char t[numChars + 1];
    memcpy(t, &word[start], numChars);
    t[numChars] = '\0';
    return t;
}

bool DSString::operator==(const char *& s) const {
    if(strcmp(word, s) == 0){
        return true;
    }
    return false;
}

DSString DSString::operator+(const char *& n) {
    char* temp1 = new char[strlen(word) + strlen(n) + 1];
    DSString temp (temp1);
    strcat(temp.word, word);
    strcat(temp.word, n);
    delete[] temp1;
    return temp;
}

//lowers the alphabetic values of a DSString
void DSString::lower() {
    for(int i = 0; i < this->getLength(); i++){
        word[i] = std::tolower(word[i]);
    }
}

//checks if a DSString location is numeric
bool DSString::is_digit(const int &c) {
    if(isdigit(word[c])){
        return true;
    }
    return false;
}

//make a dsstring from a single character
DSString &DSString::operator=(const char c) {
    delete[] word;

    word = new char[1];
    word[0] = c;
    return *this;
}

//make a DSstring into a number
int DSString::to_digit() {
    return atoi(word);
}
