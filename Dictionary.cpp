#include "Dictionary.h"
#include<list>
#include <fstream>
#include <sstream>

using std::endl;
using std::cout;




Dictionary::Dictionary(const string& filename, const string& separators):filename{filename},theSeparators{ escape_tab_newline_chars(separators) }
{
	
	std::ifstream fin(filename); // create an input file stream
	if (!fin)
	{
		std::cout << "could not open input file: " << filename << endl;
		exit(1);
	}
	int linenum = 0;
	string line;
	getline(fin, line); // very important first attempt to read;
	// this first attempt will get the i/o flags initialized
	while (fin)
	{
		//cout << line << endl;
		++linenum; // count the line
		std::istringstream sin(line); // turn the line into an input string stream
		input_lines.push_back(line);
		
		string tokenStr;
		while (sin >> tokenStr) // extract token strings
		{
			extract_and_push(tokenStr, linenum);
		}
		getline(fin, line); // attempt to read the next line, if any
	}
	fin.close();
}

size_t Dictionary::bucket_index(const string& tokenText) const
{
	int index = 26; // bucket index for tokens not beginning with a letter
	if (isalpha(tokenText[0]))
	{
		if (isupper(tokenText[0])) index = tokenText[0] - 'A';
		else index = tokenText[0] - 'a';
	}
	return index;
}

size_t Dictionary::bucket_index(const char& tokenText) const
{
	int index = 26; // bucket index for tokens not beginning with a letter
	if (isalpha(tokenText))
	{
		if (isupper(tokenText)) index = tokenText - 'A';
		else index = tokenText - 'a';
	}
	return index;
}



vector<string> Dictionary::extract_tokens_from_line(const string& line) const
{
	vector<string> seperatortext;

	size_t sndx{ line.find_first_not_of(theSeparators) };
	
		 while (sndx != std::string::npos) // while there are tokens
		 { // find the end of current token that starts at sndx
			size_t endIndex = line.find_first_of(theSeparators, sndx + 1);
		 // did we find a separator or did we reach the of line?
				if (endIndex == std::string::npos)
					{ // we did reach the of line, so set sndx to end of line
						endIndex = line.length();
					}
		// extract the token
		 std::string token{ line.substr(sndx, endIndex - sndx) };
		 // again, find the start index of next token, if any
		 sndx = line.find_first_not_of(theSeparators, endIndex + 1);
		 //cout << token << " "; // process the token before losing it!
		 seperatortext.push_back(token);
		 }
	return seperatortext;
}




// creates a token with the specified tokenText and line_number and then pushes (inserts) 
//the token at the end of the bucket list corresponding to tokenText[0].
void Dictionary::push_back_into_bucket(const string& tokenText, size_t line_number)
{
	Token text(tokenText,line_number);
	size_t index = bucket_index(tokenText);
	
	if (token_list_buckets[index].empty()) { //checks if particular bucet is empty

		token_list_buckets[index].push_back(text); //adds text to bucket if empty
		
	}
	else {
		bool notinlist = false;
		//since bucket is not empty, loop through all text in particular bucket
		list<Token>::iterator j = token_list_buckets[index].begin();
		for (j = token_list_buckets[index].begin(); j != token_list_buckets[index].end(); j++) {
			
			//compares text with tokens already in the bucket
			if (j->compare(text) == 0) {
				//if text ia already in bucket then add line number
				j->push_back_line_number(line_number);
				return; 
			}
			else {
				notinlist = true; //if text is not in bucket then set not in list to true
				
			}

		}
	
		if (notinlist) {
			//since text is not in bucket, add text to bucket
			token_list_buckets[index].push_back(text);
		}
	}
	


	
	
}

// using extract_tokens_from_line and push_back_into_bucket, inserts the tokens extracted 
//from the specified line and line_number into appropriate buckets
void Dictionary::extract_and_push(const string& line, size_t line_number)
{
	vector<string> extractedtext = extract_tokens_from_line(line); //passes tokens text to extract tokens method which removes sperator character from token text
	vector<string>::iterator i = extractedtext.begin();
	//lops through extracted text and passes text and line number to push back into bucket method
	for(i = extractedtext.begin(); i != extractedtext.end(); ++i) {
		push_back_into_bucket(*i, line_number);
	}
}


// An example of a static member function, which could otherwise be a free function.
// replaces \t and \n with \\t and \\n in separators and returns the resulting string
string Dictionary::escape_tab_newline_chars(const string& separators)
{
	string fake_tab{ "\\t" }; // two characters, \ and t
	string real_tab{ "\t" };  // one character, \t

	string temp{ separators };
	// restore tabs
	string::size_type pos = temp.find(fake_tab);
	while (pos != string::npos)
	{
		temp.replace(pos, 2, real_tab);
		pos = temp.find(fake_tab);
	}

	string fake_newline{ "\\n" }; // two characters, \ and n
	string real_newline{ "\n" };  // one character, \n

	// restore newlines
	pos = temp.find(fake_newline);
	while (pos != string::npos)
	{
		temp.replace(pos, 2, real_newline);
		pos = temp.find(fake_newline);
	}

	return temp;
}

// prints the input lines beginning with the characters stored in char_set.
void Dictionary::print_input_lines(set<char>& char_set) const
{
	//if charset is empty then print all input lines
	if (char_set.empty()) print_input_lines();
	else {
		int lineNum = 1; //initial line num
		
		set<char>::iterator itr = char_set.begin();
		//loops through all char in charset
		for (itr = char_set.begin(); itr != char_set.end(); itr++) {
			lineNum = 1;
			
			//loops through inputlines
			for (int t = 0; t < input_lines.size(); t++) {
				int x = 0;
				//if the first character of each line is a tab or space, move to the next character
				while(input_lines[t][x] == '\t' || input_lines[t][x]==' ') {
					x++;
				}
				//compares first character not a tab or space to char from charset, if they match then print particular line
				if (input_lines[t][x] == *itr) { cout << lineNum << ": " << input_lines[t] << endl; }
				lineNum++; //increments line num

			}			
		}
	
	}

}

void Dictionary::print_input_tokens(set<char>& char_set) const
{
	//if charset is empty then print all input tokens
	if (char_set.empty()) print_input_tokens();
	else {
		set<char>::iterator itr = char_set.begin();

		bool extra_bucket = false; //responsible for 26th bucket
		//loops through all ch in charset
		for (itr = char_set.begin(); itr != char_set.end(); itr++) {
			size_t index = bucket_index(*itr); //passes ch to bucket index method and retrieves index that mathches alphabet 
			if (index != 26) {
				//prints all index except the 26th bucket
				print_alphabets(index); //prints alphabets (<A>,<B>...)
				print_buckets(index); //prints buckets that corresponds with index
			}
			else {
				//sets extra bucket to true
				extra_bucket = true;
			}
			
		}
		 	
		if (extra_bucket) {
			//if extra bucket is true print the 26th bucket
			print_alphabets(26); //prints alphabets (<A>,<B>...)
			print_buckets(26); //prints buckets that corresponds with index
		}
	}
}

void Dictionary::print_sorted_on_token_text(set<char>& char_set) const
{
	//if charset is empty then print all input sorted tokens
	if (char_set.empty()) print_sorted_on_token_text();
	else {
		set<char>::iterator itr = char_set.begin(); //initializes iterator

		bool extra_bucket = false;
		//loops through all ch in charset
		for (itr; itr != char_set.end(); itr++) {
			size_t i = bucket_index(*itr); //passes ch to bucket index method and retrieves index that mathches alphabet 
			if (i != 26) {
				print_forward_list(i, 3); //prints forward list sorted by tokens of buckets corresponding to index
			}
			else {
				extra_bucket = true;
			}


		}
		if (extra_bucket) {
			print_forward_list(26, 3); //prints forward list sorted by tokens of the 26th bucket
		}
	}
}

void Dictionary::print_sorted_on_token_frequecy(set<char>& char_set) const
{
	//if charset is empty then print all input token sorted by frequency
	if (char_set.empty()) print_sorted_on_token_frequecy();
	else {
		set<char>::iterator itr = char_set.begin(); //initializes iterator

		bool extra_bucket = false;
		//loops through all ch in charset
		for (itr; itr != char_set.end(); itr++) {
			size_t i = bucket_index(*itr); //passes ch to bucket index method and retrieves index that mathches alphabet 
			if (i != 26) {
				print_forward_list(i, 1); //prints forward list sorted by frequency of buckets corresponding to index
			}
			else {
				extra_bucket = true;
			}
			

		}
		if (extra_bucket) {
			print_forward_list(26, 1); //prints forward list sorted by frequency  of the 26th bucket
		}

	}
}

void Dictionary::print_sorted_on_token_length(set<char>& char_set) const
{
	//if charset is empty then print all input tokens sorted by length
	if (char_set.empty()) print_sorted_on_token_length();
	else {

		set<char>::iterator itr = char_set.begin(); //initializes iterator
		bool extra_bucket = false;
		//loops through all ch in charset
		for (itr; itr != char_set.end(); itr++) {
			size_t i = bucket_index(*itr); //passes ch to bucket index method and retrieves index that mathches alphabet 
			if (i != 26) {
				print_forward_list(i, 2); //prints forward list sorted by length of buckets corresponding to index
			}
			else {
				extra_bucket = true;
			}


		}
		if (extra_bucket) {
			print_forward_list(26, 2); //prints forward list sorted by length  of the 26th bucket
		}
	}
}

//prints all input lines
void Dictionary::print_input_lines() const
{	
	int lineNum = 1; //line number count
	vector<string>::const_iterator i = input_lines.begin(); //initializes line number
	//loops through and prints all lines with line number
	for (i = input_lines.begin(); i != input_lines.end(); i++) {
		cout <<lineNum <<": " << *i << endl;
		lineNum++; //increments line number
	}
		

}

//prints all input tokens
void Dictionary::print_input_tokens() const
{

	//loops through and prints tokens for all 26 buckets
	for (int i = 0; i < 27; i++) {	
		print_alphabets(i);  //prints alphabets (<A>,<B>...)
		print_buckets(i); //prints buckets that corresponds with index
		
	}
}

//prints all tokens sorted by text
void Dictionary::print_sorted_on_token_text() const
{
	//loops through and prints sorted tokens for all 26 buckets
	for (int i = 0; i < 27; i++) {
		print_forward_list(i, 3);  //prints sorted tokens for buckets corresponding to index
	}

}

void Dictionary::print_sorted_on_token_frequecy() const
{
	//loops through and prints sorted tokens for all 26 buckets
	for (int i = 0; i < 27; i++) {
		print_forward_list(i, 1); //prints forward list sorted by frequency of buckets corresponding to index
	}	
}

void Dictionary::print_sorted_on_token_length() const
{
	//loops through and prints sorted tokens for all 26 buckets
	for (int i = 0; i < 27; i++) {
		print_forward_list(i, 2); //prints forward list sorted by length of buckets corresponding to index

	}
}
//prints alphabets
void Dictionary::print_alphabets(size_t index) const
{
	string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	//prints alphabets corresponding to index (<A>,<B>)
	if (index == 26) {
		cout << "<>" << endl;
	}
	else {
		cout << "<" << alphabets[index] << ">" << endl;
	}
}

//prints buckets
void Dictionary::print_buckets(size_t index) const
{
	list<Token>::const_iterator j = token_list_buckets[index].begin();
	//loops through token list buvkets of particular index and print tokens in bucket
	for (j = token_list_buckets[index].begin(); j != token_list_buckets[index].end(); j++) {
		cout << *j << endl;
	}
}

//prints sorted forward list
void Dictionary::print_forward_list(size_t index, int option) const
{
	forward_list<Token> flist{ token_list_buckets[index].begin(), token_list_buckets[index].end() }; //initializes forwardlist with tokens
	//in particular bucket corresponding to index

	if (option == 1) {
		flist.sort(isLessFrequent); //sorts by frequency
	}
	else if (option == 2) {
		flist.sort(isShorter); //sorts by length
	}
	else if(option==3) {
		flist.sort(operator<); //sorts by token
	}
	

	print_alphabets(index); //prints aplhabets

	forward_list<Token>::iterator ptr; //intializes iterator

	//loops through forward list and prints sorted list
	for (ptr = flist.begin(); ptr != flist.end(); ptr++) {
		cout << *ptr << endl;
	}
}




