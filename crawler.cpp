#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

//Evaluate passed filename
void evaluate(std::string filename, std::vector<std::string> &visited) {
	std::ifstream inputFile(filename.c_str());
	if(inputFile.good()) {
		visited.push_back(filename);
		std::string textLine;
		unsigned int count;
		bool expectParen;
		bool makingLink;
		std::string word;
		while(getline(inputFile, textLine)) {
			count = 0;
			word = "";
			makingLink = false;
			expectParen = false;
			while(count < textLine.length()) {
				if(expectParen) {
					if(textLine[count] == '(') {
						makingLink = true;
					}
					expectParen = false;
				} else if(makingLink) {
					if(textLine[count] != ')') {
						word += textLine[count];
					} else {
						if(std::find(visited.begin(), visited.end(), word) == visited.end()) {
							evaluate(word, visited);
						}
						makingLink = false;
						word = "";
					}
				} else {
					if(textLine[count] == ']') {
					expectParen = true;
					}
				}
				count++;
			}
		}
	}
	inputFile.close();
}

int main(int argc, char* argv[]) {
	std::string config;
	if(argc < 2){
		config = "config.txt";
	} else {
		config = argv[1];
	}
	std::string INDEX_FILE;
	std::string OUTPUT_FILE;
	std::ifstream configFile(config.c_str());
	std::string line;
	while(getline(configFile, line)) {
  		bool foundEquals = false;
    	bool foundFirstLetter = false;
    	char firstLetter = '0';
    	bool makingWord = false;
    	std::string word = "";
    	for(unsigned int i = 0; i < line.length(); i++) {
      		if(line[i] == '#' && !foundFirstLetter) break;
      		if(!foundFirstLetter) {
        		if(isspace(line[i]) == 0) {
          			foundFirstLetter = true;
          			firstLetter = line[i];
        		}
      		} else if(foundEquals) {
        		if(makingWord) {
          			if(isspace(line[i]) != 0 || line[i] == '#') {
            			break;
          			} else {
            			word += line[i];
          			}
        		} else {
          			if(isspace(line[i]) == 0 && line[i] != '#') {
            			word += line[i];
            			makingWord = true;
          			}
        		}
      		} else {
        		if(line[i] == '=') foundEquals = true;
      		}
    	}
    	if(foundFirstLetter) {
      		if(firstLetter == 'I') {
        		INDEX_FILE = word;
      		} else if(firstLetter == 'O') {
        		OUTPUT_FILE = word;
        	}
    	}
  	}
  	configFile.close();

  	//Seed file examination
  	std::vector<std::string> visited;
	std::ifstream seedFile(INDEX_FILE.c_str());
	line = "";
	while(getline(seedFile, line)) {
		if(line != "") {
			if(std::find(visited.begin(), visited.end(), line) == visited.end()) {
				evaluate(line, visited);
			}
		}
	}
	seedFile.close();
	std::ofstream output(OUTPUT_FILE.c_str());
	for(std::vector<std::string>::iterator it = visited.begin(); it != visited.end(); ++it) {
		output << *it << "\n";
	}
	output.close();
}