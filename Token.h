#pragma once
#include <string>
#include<vector>
#include<iostream>
#include <ostream>


using std::string;
using std::vector;
using std::ostream;

class Token {
private:
	 string text; // this token's text
	 size_t frequency; // this token's frequency at construction
	 vector<size_t> line_number_list; // this token's list of associated line numbers
	 bool not_in_list(size_t lineNum) const;

public:
	  Token(string text, size_t line_number); //constructor

	  Token() = delete; // disables default construction

	  Token(const Token & source) = default; // copy ctor

	  Token(Token && source) = default; // move ctor

	  Token& operator=(const Token& rhs) = default; // copy op=

	  Token & operator=(Token && rhs) = default; // move op=

	  ~Token() = default; // dtor
	  
	  int compare(const Token & other)const; // compares this and other token texts using std::string's compare
	  
	  void print(ostream & out) const; // prints this token's text, frequency, and list of line numbers
	  
	  string get_token_text() const;   // returns a copy of this token's text
		   
	  int get_frequency()const; // returns this token's frequency
	  
		
	  vector<size_t> get_number_list() const; // returns a copy of this token's list of line numbers
		  
	  size_t length()const;  // returns the length of this token's text
		  
	  void increment_freqency();  // increments this token's frequency
		   		  
	  void push_back_line_number(size_t lineNum);  // add a specified line number to this token's list of line numbers,only if the specified line number is not in the list.	
	  
};
bool operator<(const Token& t1, const Token& t2); // uses compare
bool isShorter(const Token& first, const Token& second); //uses length
bool isLessFrequent(const Token& first, const Token& second); // uses getFrequency
ostream& operator<<(ostream& out, const Token& sourse); // uses print