#ifndef MYSET_H
#define MYSET_H

#include <set>
#include <string>

// avoid circular reference
class WebPage;

template<typename T>
class MySet : public std::set<T>
{
public:
  MySet();
  MySet<T> set_intersection(const MySet<T>& other);
  MySet<T> set_union(const MySet<T>& other);
};

template<typename T>
MySet<T>::MySet() : std::set<T>() {}

//Returns a set of the intersect between this set and the passed set
template<typename T>
MySet<T> MySet<T>::set_intersection(const MySet<T>& other) {
	MySet<T> intersectSet;
	typename MySet<T>::iterator it;
    for(it = this->begin(); it != this->end(); ++it) {
        if(other.find(*it) != other.end()) {
        	intersectSet.insert(*it);
        }
    }
    return intersectSet;
}

//Returns a set of the union between this set and the passed set
template<typename T>
MySet<T> MySet<T>::set_union(const MySet<T>& other) {
	MySet<T> unionSet;
	typename MySet<T>::iterator it;
    for(it = this->begin(); it != this->end(); ++it) {
        unionSet.insert(*it);
    }
    for(it = other.begin(); it != other.end(); ++it) {
        unionSet.insert(*it);
    }
	return unionSet;
}

#endif
