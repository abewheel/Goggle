/*
webpage.cpp
Manages a web page's contents. Method descriptions in webpage.h
*/
#include "webpage.h"

WebPage::WebPage() {
	name = "";
}

WebPage::WebPage(std::string filename) {
	name = filename;
}

WebPage::~WebPage() {

}

void WebPage::filename(std::string fname) {
	name = fname;
}

std::string WebPage::filename() const {
	return name;
}

void WebPage::all_words(const MySet<std::string>& words) {
	text.set_union(words);
}

MySet<std::string> WebPage::all_words() const {
	return text;
}

void WebPage::add_incoming_link(WebPage* wp) {
	linkInc.insert(wp);
}

MySet<WebPage*> WebPage::incoming_links() const {
	return linkInc;
}

void WebPage::add_outgoing_link(WebPage* wp) {
	linkOut.insert(wp);
}

MySet<WebPage*> WebPage::outgoing_links() const {
	return linkOut;
}

std::ostream& operator<< (std::ostream & os, const WebPage & page) {
	std::ifstream inputFile(page.name.c_str());
	std::string line;
	bool foundBracket = false;
	bool shouldPrint = true;
	unsigned int count;
	while(getline(inputFile, line)) {
		count = 0;
		while(count < line.length()) {
			if(line[count] == ']') {
				foundBracket = true;
			} else if(foundBracket) {
				if(line[count] == '(') {
					shouldPrint = false;
				}
				foundBracket = false;
			}
			if(shouldPrint) {
				os << line[count];
			} else {
				if(line[count] == ')') {
					shouldPrint = true;
				}
			}
			count++;
		}
	}
	inputFile.close();
	return os;
}

void WebPage::addOutLinkText(MySet<std::string> links) {
	linkText = links;
}

MySet<std::string> WebPage::outLinkText() {
	return linkText;
}