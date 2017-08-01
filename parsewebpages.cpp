/*
parsewebpages.cpp
Parses the passed file and separates the content into the two
provided sets.
*/
#include "parsewebpages.h"

void ParseWebPages::parse(std::string filename,
		     MySet<std::string>& allWords,
		     MySet<std::string>& allLinks) {
	std::ifstream inputFile(filename.c_str());
	std::string line;
	unsigned int count;
	bool expectParen;
	bool makingLink;
	std::string word;
	while(getline(inputFile, line)) {
		count = 0;
		word = "";
		makingLink = false;
		expectParen = false;
		while(count < line.length()) {		//Searches file line by line
			if(expectParen) {
				if(line[count] == '(') {
					makingLink = true;
				}
				expectParen = false;
			} else if(makingLink) {
				if(line[count] != ')') {
					word += line[count];
				} else {
					allLinks.insert(word);
					makingLink = false;
					word = "";
				}
			} else if(isalnum(line[count])) {
				word += line[count];
			} else {
				if(word != "") {
					allWords.insert(word);
					word = "";
				}
				if(line[count] == ']') {
					expectParen = true;
				}
			}
			count++;
		}
	}
	inputFile.close();
}