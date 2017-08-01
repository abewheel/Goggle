#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <string>
#include <vector>
#include <sstream>
#include <map>

#include "searcheng.h"
#include "msort.h"

class MainWindow : public QWidget {
	Q_OBJECT
public:
	//Takes a SearchEng object to access collections of WebPages.
	MainWindow(SearchEng mySE, double restartProbability, int stepNumber);
	//Destructor deletes Qt Objects.
	~MainWindow();

private slots:
	//Handles press of Search button.
	void search();
	//Handles press of Examine button.
	void displayPage();
	//Handles different selections in the list on the search page.
	void changeSelected(int s);
	//Handles press of Examine button on Examine window.
	void otherExamine();
	//Handles different selections in the incoming link list.
	void otherIncChange(int s);
	//Handles different selections in the outgoing link list.
	void otherOutChange(int s);
	//Handles the closing of the Search window.
	void closeBoth();
	//Handles the closing of the Examine window.
	void otherClose();

private:
	//Fills the Examine window with information from the passed page.
	//UseSearchSort should be true if the Examine button on the Search window
	//was pressed, false if the Examine button on the Examine window was pressed.
	void populateOther(WebPage* current, bool useSearchSort);

	SearchEng se;

	QVBoxLayout* overallLayout;
	QHBoxLayout* searchLayout;
	QVBoxLayout* radioButtonsLayout;
	QHBoxLayout* resultsLayout;
	QVBoxLayout* sortButtonsLayout;

	QLabel* searchLabel;
	QLineEdit* searchInput;
	QRadioButton* singleRadio;
	QRadioButton* andRadio;
	QRadioButton* orRadio;
	QPushButton* searchButton;

	QLabel* resultsLabel;
	QListWidget* resultsListWidget;
	QPushButton* examineButton;
	QLabel* sortLabel;
	QButtonGroup* sorting;
	QRadioButton* pagerankSortRadio;
	QRadioButton* fileSortRadio;
	QRadioButton* incSortRadio;
	QRadioButton* outSortRadio;

	QPushButton* quitButton;

	QWidget* other;
	QVBoxLayout* otherOverallLayout;
	QLabel* name;
	QTextEdit* contents;
	QHBoxLayout* otherLinksHeaderLayout;
	QLabel* incLabel;
	QLabel* outLabel;
	QHBoxLayout* otherLinksLayout;
	QListWidget* incListWidget;
	QListWidget* outListWidget;
	QPushButton* otherExamineButton;
	QPushButton* otherQuitButton;
	QVBoxLayout* otherSortButtonsLayout;
	QLabel* otherSortLabel;
	QButtonGroup* otherSorting;
	QRadioButton* otherFileSortRadio;
	QRadioButton* otherIncSortRadio;
	QRadioButton* otherOutSortRadio;

	int selectedItem;
	int otherSelectedItem;
	int otherLastChange;
	std::vector<WebPage*> sortedResults;
	std::vector<WebPage*> sortedInc;
	std::vector<WebPage*> sortedOut;
	double RESTART_PROBABILITY;
  	int STEP_NUMBER;
};

#endif