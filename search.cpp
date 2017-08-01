#include <QApplication>

#include "mainwindow.h"
#include "parsewebpages.h"
#include "searcheng.h"

int main(int argc, char* argv[])
{
  std::string config;
  if(argc < 2){
    config = "config.txt";
  } else {
    config = argv[1];
  }
  std::string INDEX_FILE;
  double RESTART_PROBABILITY = 0;
  int STEP_NUMBER = 0;
  std::ifstream configFile(config.c_str());
  std::string line;

  //Read config file
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
          } else if(firstLetter == 'R') {
            RESTART_PROBABILITY = atof(word.c_str());
          } else if(firstLetter == 'S') {
            STEP_NUMBER = atoi(word.c_str());
          }
      }
  }
  configFile.close();

  SearchEng se;
  PageParser *parser = new ParseWebPages();
  se.add_parse_from_index_file(INDEX_FILE, parser);
  se.add_links(); //MUST BE CALLED TO POPULATE WEBPAGE'S SETS OF LINKS
  delete parser;
  QApplication app(argc, argv);
  MainWindow mainWindow(se, RESTART_PROBABILITY, STEP_NUMBER);
  mainWindow.show();
  return app.exec();
}