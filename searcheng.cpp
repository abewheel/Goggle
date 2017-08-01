/*
searcheng.cpp
Manages the back end of searching. Method documentation in searcheng.h
*/
#include "searcheng.h"

SearchEng::SearchEng() {

}

SearchEng::~SearchEng() {

}

void SearchEng::add_parse_from_index_file(std::string index_file, PageParser* parser) {
	std::ifstream inputFile(index_file.c_str());
	std::string line;
	while(getline(inputFile, line)) {
		if(line != "") {
			add_parse_page(line, parser);
		}
	}
}

void SearchEng::add_parse_page(std::string filename, PageParser* parser) {
	MySet<std::string> text;
	MySet<std::string> linkText;
	parser->parse(filename, text, linkText);
	WebPage * wp = new WebPage(filename);
	all.insert(wp);
	wp->all_words(text);
	MySet<std::string>::iterator it;
	std::string current;
    for(it = text.begin(); it != text.end(); ++it) {
    	current = convToLower(*it);
    	if(wordToPages.find(current) == wordToPages.end()) {
    		std::set<WebPage*> s;
    		s.insert(wp);
    		wordToPages.insert(std::pair<std::string,std::set<WebPage*> >(current, s));
    	} else {
    		wordToPages[current].insert(wp);
    	}
    }
    wp->addOutLinkText(linkText);
}

std::set<WebPage*> SearchEng::getPages(std::string word) {
	return wordToPages[word];
}

MySet<WebPage*> SearchEng::getPagesAsMySet(std::string filename) {
	MySet<WebPage*> setWP;
	std::set<WebPage*> requestedPages = getPages(filename);
	std::set<WebPage*>::iterator it;
	for(it = requestedPages.begin(); it != requestedPages.end(); ++it) {
		setWP.insert(*it);
	}
	return setWP;
}

void SearchEng::add_links() {
	std::set<WebPage*>::iterator it;
	std::set<WebPage*>::iterator it0;
	MySet<std::string>::iterator it1;
	MySet<std::string> links;
	for(it = all.begin(); it != all.end(); ++it) {				//*it is each webpage
    	links = (*it)->outLinkText();
    	for(it1 = links.begin(); it1 != links.end(); ++it1) {	//*it1 is each outgoing link string
    		for(it0 = all.begin(); it0 != all.end(); ++it0) {	//*it0 is also a webpage
    			if((*it0)->filename() == *it1) {
    				(*it)->add_outgoing_link(*it0);
    				(*it0)->add_incoming_link(*it);
    			}
    		}
    	}
    }
}

void SearchEng::deletePages() {
	std::set<WebPage*>::iterator it;
    for(it = all.begin(); it != all.end(); ++it) {
    	delete(*it);
    }
}