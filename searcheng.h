#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <set>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include "util.h"

class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  void add_parse_from_index_file(std::string index_file, 
				 PageParser* parser);
  void add_parse_page(std::string filename, 
		      PageParser* parser);

  /**** Add other desired member functions here *****/
  //Returns a std::set of WebPages the word maps to
  std::set<WebPage*> getPages(std::string word);

  //Adds incoming and outgoing links to the webpages
  void add_links();

  //returns a MySetWebPage of the WebPages the word maps to
  MySet<WebPage*> getPagesAsMySet(std::string word);

  //Deletes all webpages
  void deletePages();

 private:
  /**** Add other desired data members here *****/
  std::map<std::string, std::set<WebPage*> > wordToPages;
  std::set<WebPage*> all;
};

#endif
