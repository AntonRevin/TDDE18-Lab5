#ifndef _CLEANER_H_
#define _CLEANER_H_

#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <string>

class Cleaner {
   private:
    std::list<std::string> validWords;
    std::list<std::pair<std::string, int>> frequencyPairs;
    int largestWordSize;

   public:
    Cleaner();
    void addWord(std::string potentialWord);
    void dynamicPrint(std::function<void(std::pair<std::string const&, int> const&)> const& printFunction);
    void sort(std::function<bool(std::pair<std::string const&, int> const&, std::pair<std::string const&, int> const&)> const& comparator);
    void printOrdered(int const limit);
    int getLargestWordSize();
    ~Cleaner();
};

#endif
