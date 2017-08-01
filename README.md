# Goggle

## Description

Goggle is a simpified search engine that bears no resemblance to Google whatsoever. It consists of a rudimentary web crawler, markdown parser, and page rank system.


## About the Project

I wrote Goggle in 2015 as an assignment for a Data Structures and Algorithms course. 


## Technical Details

Goggle is written in C++ and uses a Qt GUI.

```
Crawler:
	Compile: g++ -g -Wall crawler.cpp -o crawler.o
	Run: ./crawler.o
	or   ./crawler.o configfile.txt

Search:
	Compile: qmake
		 make
	Run: ./search
	or   ./search configfile.txt
```
