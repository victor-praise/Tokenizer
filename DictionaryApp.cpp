
#include <iostream>
#include "Token.h"
#include "Dictionary.h"
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;


int main(){

	cout << "Enter the name of input text file: ";
	string filename;
	std::cin >> filename;
	std::cin.ignore();
	string seperator{};
	cout << "Enter seperators: ";
	std::getline(std::cin, seperator);	
	string option;
	Dictionary tokenizer(filename,seperator);

	//continously calls menu untill user enters 0
	do
	{

		cout << "Choose one of the options listed below and, optionally," << endl;
		cout << "enter the initial character of the tokens to print :" << endl;
		cout <<" 1 - Print input lines" << endl;
		cout <<" 2 - Print original unsorted tokens" << endl;
		cout <<" 3 - Print tokens sorted by text" << endl;
		cout <<" 4 - Print tokens sorted by frequency" << endl;
		cout <<" 5 - Print tokens sorted by length" << endl;
		cout <<" 0 - Exit" << endl;
		cout <<" Enter your input : ";

		std::cin >> option; //takes user menu input
		std::set<char> char_set(option.begin() + 1, option.end()); ///creates a set starting from the second character in user's input
		cout << "Dictionary Source File: " << filename << endl;
		cout << "Separator characters: " << tokenizer.escape_tab_newline_chars(seperator) << endl;
		switch (option[0]) //uses first character in user's input
		{
		case '1':
			cout << "input lines" << endl;
			cout << "===========" << endl;
			tokenizer.print_input_lines(char_set); //prints input lines
			break;
		case '2':
			cout << "Dictionary Unsorted" << endl;
			cout << "===================" << endl;
			tokenizer.print_input_tokens(char_set); //prints unsorted tokens
			break;
		case '3':
			cout << "Dictionary sorted by token text" << endl;
			cout << "===============================" << endl;
			tokenizer.print_sorted_on_token_text(char_set); //prints tokens sorted by text
			break;
		case '4':
			cout << "Dictionary sorted by token frequency" << endl;
			cout << "===================================" << endl;
			tokenizer.print_sorted_on_token_frequecy(char_set); //prints token sorted by frequency
			break;
		case '5':
			cout << "Dictionary sorted by token length" << endl;
			cout << "=================================" << endl;
			tokenizer.print_sorted_on_token_length(char_set); //prints token sorted by length
			break;
		default:
			break;
		}
	} while (option[0] != '0');

	cout << "Goodbye." << endl;
	
	exit(0);
}