#ifndef PARSEWEBPAGES_H
#define PARSEWEBPAGES_H

#include <fstream>
#include <string>
#include "pageparser.h"

class ParseWebPages : public PageParser {
public:
	//Parses the passed file and sorts its contents into sets
	void parse(std::string filename,
		     MySet<std::string>& allWords,
		     MySet<std::string>& allLinks);
};

#endif