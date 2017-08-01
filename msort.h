/*
msort.h
Performs merge sort on a vector.
*/
#ifndef MSORT_H
#define MSORT_H

#include <vector>
#include <map>
#include "webpage.h"

//Merge Sort helper method. Performs merging of vectors.
template <class T, class Comparator>
void merge(std::vector<T>& myArray, int l, int r, int mid, Comparator comp) {
    T aux[myArray.size()];
    int i = l;
    int j = mid + 1;
    int current = l;
    while(i <= mid && j <= r) {
        if(comp(myArray[i], myArray[j])) {
            aux[current] = myArray[i];
            i++;
        } else {
            aux[current] = myArray[j];
            j++;
        }
        current++;
    }
    while (i <= mid) {
        aux[current] = myArray[i];
        current++;
        i++;
    }
    while (j <= r) {
        aux[current] = myArray[j];
        current++;
        j++;
    }
    for(i = l; i < current; i++) {
        myArray[i] = aux[i];
    }
}

//Merge Sort helper method. Reduces vector using recursion.
template <class T, class Comparator>
void msortH(std::vector<T>& myArray, int l, int r, Comparator comp) {
    if(l >= r) return;
    int mid = (l + r) / 2;
    msortH(myArray, l, mid, comp);
    msortH(myArray, mid + 1, r, comp);
    merge(myArray, l, r, mid, comp);
}

//Performs Merge Sort on the given vector using the passed comparator.
template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, Comparator comp) {
	msortH(myArray, 0, myArray.size() - 1, comp);

}

//Comparator for PageRank.
struct pageRankComp {
    std::map<WebPage*, double> pageRanks;
    bool operator()(const WebPage* lhs, const WebPage* rhs) {
        double lhsVal = 0;
        double rhsVal = 0;
        for(std::map<WebPage*, double>::iterator itr = pageRanks.begin(); itr != pageRanks.end(); ++itr) {
            if(itr->first->filename() == lhs->filename()) lhsVal = pageRanks[itr->first];
            if(itr->first->filename() == rhs->filename()) rhsVal = pageRanks[itr->first];
        }
        return lhsVal < rhsVal; 
    }
};

//Comparator for WebPage filenames.
struct filenameComp {
	bool operator()(const WebPage* lhs, const WebPage* rhs) {
		return lhs->filename() < rhs->filename(); 
	}
};

//Comparator for WebPage incoming links.
struct incComp {
    bool operator()(const WebPage* lhs, const WebPage* rhs) {
      return lhs->incoming_links().size() < rhs->incoming_links().size(); 
    }
};

//Comparator for WebPage outgoing links.
struct outComp {
    bool operator()(const WebPage* lhs, const WebPage* rhs) {
      return lhs->outgoing_links().size() < rhs->outgoing_links().size(); 
    }
};
#endif