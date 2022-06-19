#include "Token.h"
#include <string>
#include <iomanip>

using std::string;
using std::cout;


//constructor (initializes the frequency to 1)
Token::Token(string text, size_t line_number): frequency{1}
{
	
	this->text=text; //sets text to this token's text
	line_number_list.push_back(line_number); //adds linenumber to line number list
}

//compares token's text with another token's text
int Token::compare(const Token& other) const
{	
	//returns 1, 0 , or less that 0 based on comparison
	return text.compare(other.text);
}

//prints token,frequency and number list
void Token::print(ostream& out) const
{
	out << std::setw(15); //left align
	out  << text << " " << "(" << frequency << ") ";

	//prints number list
	for (auto i = line_number_list.begin(); i != line_number_list.end(); i++) {
		cout << *i << " ";
	}
}

string Token::get_token_text() const
{
	string tokenText = this->text; //copies token's text

	return tokenText; //returns a copy of token's text
}

//returns frequency
int Token::get_frequency() const
{
	return frequency;
}

//returns a copy of number list
vector<size_t> Token::get_number_list() const
{
	vector<size_t> list = line_number_list;

	return list;
}

//returns text's length
size_t Token::length() const
{
	return text.length();
}

//increments frequency
void Token::increment_freqency()
{
	frequency++;
}

//
bool Token::not_in_list(size_t lineNum) const
{

	for (auto i = line_number_list.begin(); i != line_number_list.end(); i++) {
		if (*i == lineNum) return false;
	}
	return true;
}

void Token::push_back_line_number(size_t lineNum)
{
	if (not_in_list(lineNum)) {
		line_number_list.push_back(lineNum);	
	}
	increment_freqency();

}

bool operator<(const Token& t1, const Token& t2)
{
	if (t1.compare(t2) > 0) return false;

	return true;
}

bool isLessFrequent(const Token& first, const Token& second)
{
	if (first.get_frequency() < second.get_frequency()) return true;
	if (first.get_frequency() > second.get_frequency()) return false;
	// since the two suppplied tokens are of the same frequency
	// we order them lexicography.
	// return (first.compare(second) < 0); // or, equivalently
	if (first.compare(second) < 0) return true;
	return false;
}

bool isShorter(const Token& first, const Token& second)
{
	if (first.length() < second.length()) return true;
	if (first.length() > second.length()) return false;
	// since the two suppplied tokens are of the same length
	// we order them lexicography.
	// return (first.compare(second) < 0); // or, equivalently
	if (first.compare(second) < 0) return true;
	return false;
}

ostream& operator<<(ostream& out, const Token& sourse)
{
	//calls the print method
	sourse.print(out);
	return out;
}
