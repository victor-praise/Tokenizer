#pragma once
#include<iostream>
#include <fstream>
#include<string>
#include<list>
#include<array>
#include<vector>
#include<set>
#include <forward_list>

#include "token.h"

using std::forward_list;
using std::set;
using std::vector;
using std::string;
using std::ostream;
using std::array;
using std::list;

class Dictionary {
private:
	string filename; // input file name
	const string theSeparators; // the separator characters in a std::string
	vector<string> input_lines; // the lines in the input file
	array<list<Token>, 27> token_list_buckets; // array of 27 token list buckets
	size_t bucket_index(const string & tokenText) const; // returns the index of the bucket corresponding to tokenText[0]
	size_t bucket_index(const char& tokenText) const; // returns the index of the bucket corresponding to tokenText[0]
	void print_alphabets(size_t index) const; //prints alphabets beside tokens
	void print_buckets(size_t index) const; //prints bucket list
	void print_forward_list(size_t index, int option) const; //prints forward list
	// extracts and returns the tokens separated by theSeparators in the specified line
	vector<string> extract_tokens_from_line(const string & line) const;// An example of a static member function, which could otherwise be a free function.
	 // replaces \t and \n with \\t and \\n in separators and returns the resulting string
	
	void push_back_into_bucket(const string & tokenText, size_t line_number); // creates a token with the specified tokenText and line_number and then pushes (inserts) the token at the end of the bucket list corresponding to tokenText[0].
	void extract_and_push(const string & line, size_t line_number); // using extract_tokens_from_line and push_back_into_bucket, inserts the tokens extracted from the specified line and line_number into appropriate buckets
	
public:
	
	Dictionary(const string & filename, const string & separators = " \t\n"); // normal constrcutor
	Dictionary() = delete;
	~Dictionary() = default;     //  default  dtor
	Dictionary(const  Dictionary&) = default;     //  copy  ctor Dictionary(              
	Dictionary(Dictionary&&) = default; // move ctor
	Dictionary & operator=(const Dictionary&) = default; // copy assignment
	Dictionary & operator=(Dictionary&&) = default;
	static string escape_tab_newline_chars(const string& separators);

	// prints the input lines beginning with the characters stored in char_set.
	// each line is preceded by its line numbers in the input file.
	// if char_set is empty, then it prints all input lines.
	void print_input_lines(set<char>&char_set) const;
	// For each character ch in char-set:
	// if ch is a letter, it prints original unsorted bucket corresponding to ch;
	// if ch is not a letter, it prints the original unsorted foreign bucket.
	void print_input_tokens(set<char>&char_set) const;
	// prints tokens sorted on token text
	void print_sorted_on_token_text(set<char>&char_set)const;
	// prints tokens sorted on token frequecy
	void print_sorted_on_token_frequecy(set<char>&char_set)const;
	// prints tokens sorted on token length
	void print_sorted_on_token_length(set<char>&char_set)const;
	void print_input_lines() const; // prints all input lines, each preceded by line number
	void print_input_tokens() const; // prints original unsorted tokens
	void print_sorted_on_token_text()const; // prints all buckets sorted on token text
	void print_sorted_on_token_frequecy()const; // prints all buckets sorted on token frequecy
	void print_sorted_on_token_length()const; // prints all buckets sorted on token length


};