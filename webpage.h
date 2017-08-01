#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <string>
#include <fstream>
#include <iostream>
#include "myset.h"
#include "parsewebpages.h"

class WebPage
{
 public:
  WebPage();

  WebPage(std::string filename);

  ~WebPage();

  /**
   * Sets the filename/URL of this webpage
   */
  void filename(std::string fname);

  /**
   * Returns the filename/URL of this webpage
   */
  std::string filename() const;

  /**
   * Updates the set containing all unique words in the text
   *  with the contents of the input parameter words
   */
  void all_words(const MySet<std::string>& words);

  /**
   * Returns all the unique, tokenized words in this webpage 
   */
  MySet<std::string> all_words() const;

  /**
   * Adds a webpage that links to this page
   */
  void add_incoming_link(WebPage* wp);

  /**
   * Returns all webpages that link to this page
   */
  MySet<WebPage*> incoming_links() const;

  /**
   * Adds a webpage that this page links to
   */
  void add_outgoing_link(WebPage* wp);

  /**
   * Returns all webpages this page links to
   */
  MySet<WebPage*> outgoing_links() const;

  /**
   * Displays the webpage text to the screen 
   */
  friend std::ostream & operator<< (std::ostream & os, const WebPage & page);

  /**** Add other desired member functions here *****/
  void addOutLinkText(MySet<std::string> links);

  MySet<std::string> outLinkText();

 private:
  std::string name;
  MySet<std::string> text;
  MySet<std::string> linkText;
  MySet<WebPage*> linkInc;
  MySet<WebPage*> linkOut;
  /**** Add other desired data members here *****/

  
};
#endif
