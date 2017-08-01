#include "mainwindow.h"

MainWindow::MainWindow(SearchEng mySE, double restartProbability, int stepNumber) {
	se = mySE;
	RESTART_PROBABILITY = restartProbability;
	STEP_NUMBER = stepNumber;
	
	//Assemble Search Window layouts
	setWindowTitle("Search");
	overallLayout = new QVBoxLayout();
	searchLayout = new QHBoxLayout();
	overallLayout->addLayout(searchLayout);
	resultsLabel = new QLabel("Results:");
	overallLayout->addWidget(resultsLabel);
	resultsLayout = new QHBoxLayout();
	sortButtonsLayout = new QVBoxLayout();
	overallLayout->addLayout(resultsLayout);

	//Assemble row of Search widgets
	searchLabel = new QLabel("Term(s):");
	searchLayout->addWidget(searchLabel);
	searchInput = new QLineEdit();
	searchLayout->addWidget(searchInput);
	connect(searchInput, SIGNAL(returnPressed()), this, SLOT(search()));

	//Assemble Search radio buttons
	radioButtonsLayout = new QVBoxLayout();
	searchLayout->addLayout(radioButtonsLayout);
	singleRadio = new QRadioButton("Single", this);
	singleRadio->setChecked(true);
	radioButtonsLayout->addWidget(singleRadio);
	andRadio = new QRadioButton("And", this);
	radioButtonsLayout->addWidget(andRadio);
	orRadio = new QRadioButton("Or", this);
	radioButtonsLayout->addWidget(orRadio);

	//Assemble Search button
	searchButton = new QPushButton("Search");
	connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
	searchLayout->addWidget(searchButton);

	//Assemble row of result displaying widgets
	resultsListWidget = new QListWidget();
	connect(resultsListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(changeSelected(int)));
	resultsLayout->addWidget(resultsListWidget);
	resultsLayout->addLayout(sortButtonsLayout);
	examineButton = new QPushButton("Examine");
	connect(examineButton, SIGNAL(clicked()), this, SLOT(displayPage()));
	examineButton->setEnabled(false);
	sortButtonsLayout->addWidget(examineButton);
	sortLabel = new QLabel("Sorted By:");
	sortButtonsLayout->addWidget(sortLabel);
	sorting = new QButtonGroup();
	pagerankSortRadio = new QRadioButton("PageRank");
	pagerankSortRadio->setChecked(true);
	sorting->addButton(pagerankSortRadio);
	sortButtonsLayout->addWidget(pagerankSortRadio);
	fileSortRadio = new QRadioButton("Filename");
	sorting->addButton(fileSortRadio);
	sortButtonsLayout->addWidget(fileSortRadio);
	incSortRadio = new QRadioButton("# Incoming");
	sorting->addButton(incSortRadio);
	sortButtonsLayout->addWidget(incSortRadio);
	outSortRadio = new QRadioButton("# Outgoing");
	sorting->addButton(outSortRadio);
	sortButtonsLayout->addWidget(outSortRadio);

	//Assemble bottom row (Quit button)
	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(closeBoth()));
	overallLayout->addWidget(quitButton);

	//Assemble other Window
	other = new QWidget();
	otherOverallLayout = new QVBoxLayout();
	other->setLayout(otherOverallLayout);
	name = new QLabel();
	otherOverallLayout->addWidget(name);
	contents = new QTextEdit();
	otherOverallLayout->addWidget(contents);
	otherLinksHeaderLayout = new QHBoxLayout();
	otherOverallLayout->addLayout(otherLinksHeaderLayout);
	incLabel = new QLabel("Incoming Links:");
	otherLinksHeaderLayout->addWidget(incLabel);
	outLabel = new QLabel("Outgoing Links:");
	otherLinksHeaderLayout->addWidget(outLabel);
	otherLinksLayout = new QHBoxLayout();
	otherOverallLayout->addLayout(otherLinksLayout);
	incListWidget = new QListWidget();
	connect(incListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(otherIncChange(int)));
	otherLinksLayout->addWidget(incListWidget);
	outListWidget = new QListWidget();
	connect(outListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(otherOutChange(int)));
	otherLinksLayout->addWidget(outListWidget);
	otherSortButtonsLayout = new QVBoxLayout();
	otherLinksLayout->addLayout(otherSortButtonsLayout);
	otherExamineButton = new QPushButton("Examine");
	otherExamineButton->setEnabled(false);
	connect(otherExamineButton, SIGNAL(clicked()), this, SLOT(otherExamine()));
	otherSortButtonsLayout->addWidget(otherExamineButton);
	otherQuitButton = new QPushButton("Quit");
	connect(otherQuitButton, SIGNAL(clicked()), this, SLOT(otherClose()));
	otherOverallLayout->addWidget(otherQuitButton);

	//Assemble other Window sort widgets
	otherSortLabel = new QLabel("Sorted By:");
	otherSortButtonsLayout->addWidget(otherSortLabel);
	otherSorting = new QButtonGroup();
	otherFileSortRadio = new QRadioButton("Filename");
	otherFileSortRadio->setChecked(true);
	otherSorting->addButton(otherFileSortRadio);
	otherSortButtonsLayout->addWidget(otherFileSortRadio);
	otherIncSortRadio = new QRadioButton("# Incoming");
	otherSorting->addButton(otherIncSortRadio);
	otherSortButtonsLayout->addWidget(otherIncSortRadio);
	otherOutSortRadio = new QRadioButton("# Outgoing");
	otherSorting->addButton(otherOutSortRadio);
	otherSortButtonsLayout->addWidget(otherOutSortRadio);

	setLayout(overallLayout);
}

MainWindow::~MainWindow() {
	se.deletePages();
	delete otherQuitButton;
	delete otherOutSortRadio;
	delete otherIncSortRadio;
	delete otherFileSortRadio;
	delete otherSorting;
	delete otherSortLabel;
	delete otherSortButtonsLayout;
	delete otherExamineButton;
	delete outListWidget;
	delete incListWidget;
	delete otherLinksLayout;
	delete outLabel;
	delete incLabel;
	delete otherLinksHeaderLayout;
	delete contents;
	delete name;
	delete otherOverallLayout;
	delete other;
	delete quitButton;
	delete outSortRadio;
	delete incSortRadio;
	delete fileSortRadio;
	delete pagerankSortRadio;
	delete sorting;
	delete sortLabel;
	delete examineButton;
	delete resultsListWidget;
	delete resultsLabel;
	delete searchButton;
	delete orRadio;
	delete andRadio;
	delete singleRadio;
	delete searchInput;
	delete searchLabel;
	delete sortButtonsLayout;
	delete resultsLayout;
	delete radioButtonsLayout;
	delete searchLayout;
	delete overallLayout;
}

void MainWindow::search() {
	sortedResults.clear();
	examineButton->setEnabled(false);
	resultsListWidget->clear();
	std::string myLine = searchInput->text().toStdString();
	std::vector<std::string> tokens;
    std::stringstream ss(myLine);
    std::string word;
    while (getline(ss, word, ' ')) {
      if (!word.empty()) {
        tokens.push_back(word);
      }
    }
    MySet<WebPage*> results;
	if(singleRadio->isChecked() && tokens.size() == 1) {
		results = se.getPagesAsMySet(convToLower(myLine));
	}
	if(andRadio->isChecked() && tokens.size() > 1) {
		results = se.getPagesAsMySet(convToLower(tokens[0]));
        for(unsigned int i = 1; i < tokens.size(); i++) {
          results = results.set_intersection(se.getPagesAsMySet(convToLower(tokens[i])));
        }
	}
	if(orRadio->isChecked() && tokens.size() > 1) {
		results = se.getPagesAsMySet(convToLower(tokens[0]));
        for(unsigned int i = 1; i < tokens.size(); i++) {
          MySet<WebPage*> current = se.getPagesAsMySet(convToLower(tokens[i]));
          results = results.set_union(current);
        }
	}
	for(MySet<WebPage*>::iterator it = results.begin(); it != results.end(); ++it) {		//Expanded results
		if(std::find(sortedResults.begin(), sortedResults.end(), *it) == sortedResults.end()) {
			sortedResults.push_back(*it);
			MySet<WebPage*> incoming = (*it)->incoming_links();
			for(MySet<WebPage*>::iterator it1 = incoming.begin(); it1 != incoming.end(); ++it1) {
				if(std::find(sortedResults.begin(), sortedResults.end(), *it1) == sortedResults.end()) {
					sortedResults.push_back(*it1);
				}
			}
			MySet<WebPage*> outgoing = (*it)->outgoing_links();
			for(MySet<WebPage*>::iterator it2 = outgoing.begin(); it2 != outgoing.end(); ++it2) {
				if(std::find(sortedResults.begin(), sortedResults.end(), *it2) == sortedResults.end()) {
					sortedResults.push_back(*it2);
				}
			}
		}
	}
	if(pagerankSortRadio->isChecked()) {
		std::map<WebPage*, double> pageranks;
		std::map<WebPage*, double> aux;
		double beginChance = (double) 1 / sortedResults.size();
		double randomVisit = RESTART_PROBABILITY / sortedResults.size();
		for(unsigned int i = 0; i < sortedResults.size(); i++) {													//Initialize all ranks equal
			pageranks.insert(std::pair<WebPage*, double>(sortedResults[i], beginChance));
			aux.insert(std::pair<WebPage*, double>(sortedResults[i], beginChance));
		}
		double sum;
		for(int i = 0; i < STEP_NUMBER; i++) {
			for(unsigned int j = 0; j < sortedResults.size(); j++) {
				sum = 0;
				MySet<WebPage*> incoming = sortedResults[j]->incoming_links();
				for(MySet<WebPage*>::iterator it1 = incoming.begin(); it1 != incoming.end(); ++it1) {				//Evaluate each's incoming links
					if(std::find(sortedResults.begin(), sortedResults.end(), *it1) != sortedResults.end()) {		//only if it is a candidate
						MySet<WebPage*> outgoing = (*it1)->outgoing_links();
						int sumOut = 1;																				//out self link
						for(MySet<WebPage*>::iterator it2 = outgoing.begin(); it2 != outgoing.end(); ++it2) {
							if(std::find(sortedResults.begin(), sortedResults.end(), *it2) != sortedResults.end()) {
								sumOut++;
							}
						}
						sum += (pageranks[*it1] / sumOut);
					}
				}
				int selfSumOut = 1;
				MySet<WebPage*> outgoing = sortedResults[j]->outgoing_links();
				for(MySet<WebPage*>::iterator it2 = outgoing.begin(); it2 != outgoing.end(); ++it2) {
					if(std::find(sortedResults.begin(), sortedResults.end(), *it2) != sortedResults.end()) {
						selfSumOut++;
					}
				}
				sum += (pageranks[sortedResults[j]] / selfSumOut);													//in self link
				aux[sortedResults[j]] = (1 - RESTART_PROBABILITY) * sum + randomVisit;
			}

			for(std::map<WebPage*, double>::iterator it = aux.begin(); it != aux.end(); ++it) {
				pageranks[it->first] = it->second;
				
			}
		}
		pageRankComp pC;
		pC.pageRanks = pageranks;
		mergeSort(sortedResults, pC);
	}
	if(fileSortRadio->isChecked()) {
		filenameComp fC;
		mergeSort(sortedResults, fC);
	}
	if(incSortRadio->isChecked()) {
		incComp iC;
		mergeSort(sortedResults, iC);
	}
	if(outSortRadio->isChecked()) {
		outComp oC;
		mergeSort(sortedResults, oC);
	}
	if(sortedResults.size() == 0) {
		resultsListWidget->addItem("No results");
	} else {
		int inc;
		int out;
		std::stringstream sstm;
		for(unsigned int i = 0; i < sortedResults.size(); i++) {
			inc = (sortedResults[i]->incoming_links()).size();
			out = (sortedResults[i]->outgoing_links()).size();
			sstm.str("");
			sstm << sortedResults[i]->filename() << "  Inc: " << inc << "  Out: " << out;
			resultsListWidget->addItem(QString::fromStdString(sstm.str()));
		}
	}
	searchInput->setText("");
}

void MainWindow::displayPage() {
	WebPage* current = sortedResults[selectedItem];
	populateOther(current, true);
	other->show();
}

void MainWindow::changeSelected(int s) {
	selectedItem = s;
	if(sortedResults.size() > 0) {
		examineButton->setEnabled(true);
	}
}

void MainWindow::otherExamine() {
	if(otherLastChange == 0) {
		populateOther(sortedInc[otherSelectedItem], false);
	} else {
		populateOther(sortedOut[otherSelectedItem], false);
	}
}

void MainWindow::otherIncChange(int s) {
	otherExamineButton->setEnabled(true);
	otherSelectedItem = s;
	otherLastChange = 0;
}

void MainWindow::otherOutChange(int s) {
	otherExamineButton->setEnabled(true);
	otherSelectedItem = s;
	otherLastChange = 1;
}

void MainWindow::closeBoth() {
	otherClose();
	close();
}

void MainWindow::otherClose() {
	other->hide();
}

void MainWindow::populateOther(WebPage* current, bool useSearchSort) {
	sortedInc.clear();
	sortedOut.clear();
	incListWidget->clear();
	outListWidget->clear();
	otherExamineButton->setEnabled(false);
	name->setText(QString::fromStdString(current->filename()));
	std::stringstream sstm;
	sstm << *(current);
	contents->setText(QString::fromStdString(sstm.str()));
	MySet<WebPage*> incSet = current->incoming_links();
	MySet<WebPage*> outSet = current->outgoing_links();
	for(MySet<WebPage*>::iterator it = incSet.begin(); it != incSet.end(); ++it) {
		sortedInc.push_back(*it);
	}
	for(MySet<WebPage*>::iterator it = outSet.begin(); it != outSet.end(); ++it) {
		sortedOut.push_back(*it);
	}

	//Selects correct radio button on Examine window if sorting Comparator changed
	//on Search window.
	if(useSearchSort) {
		if(fileSortRadio->isChecked() || pagerankSortRadio->isChecked()) {
			otherFileSortRadio->setChecked(true);
		} else if(incSortRadio->isChecked()) {
			otherIncSortRadio->setChecked(true);
		} else {
			otherOutSortRadio->setChecked(true);
		}
	}

	//Performs sorting with desired Comparator.
	if((useSearchSort && fileSortRadio->isChecked()) || otherFileSortRadio->isChecked()) {
		filenameComp fC;
		mergeSort(sortedInc, fC);
		mergeSort(sortedOut, fC);
	}
	if((useSearchSort && incSortRadio->isChecked()) || otherIncSortRadio->isChecked()) {
		incComp iC;
		mergeSort(sortedInc, iC);
		mergeSort(sortedOut, iC);
	}
	if((useSearchSort && outSortRadio->isChecked()) || otherOutSortRadio->isChecked()) {
		outComp oC;
		mergeSort(sortedInc, oC);
		mergeSort(sortedOut, oC);
	}
	int inc;
	int out;

	//Populate Incoming Links.
	for(unsigned int i = 0; i < sortedInc.size(); i++) {
		sstm.str("");
		inc = (sortedInc[i]->incoming_links()).size();
		out = (sortedInc[i]->outgoing_links()).size();
		sstm << sortedInc[i]->filename() << "  Inc: " << inc << "  Out: " << out;
		incListWidget->addItem(QString::fromStdString(sstm.str()));
	}

	//Populate Outgoing links.
	for(unsigned int i = 0; i < sortedOut.size(); i++) {
		sstm.str("");
		inc = (sortedOut[i]->incoming_links()).size();
		out = (sortedOut[i]->outgoing_links()).size();
		sstm << sortedOut[i]->filename() << "  Inc: " << inc << "  Out: " << out;
		outListWidget->addItem(QString::fromStdString(sstm.str()));
	}
}