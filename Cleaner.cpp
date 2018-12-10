#include "Cleaner.h"

Cleaner::Cleaner() : validWords{}, frequencyPairs{}, largestWordSize{} {
}

void Cleaner::addWord(std::string potentialWord) {
}

void Cleaner::printOrdered(int const limit) {
    int currentSize{};
    for (std::string currentWord : validWords) {
        if ((currentSize + currentWord.size() + 1) < limit) {
            currentSize += currentWord.size();
            std::cout << currentWord << " ";
        } else {
            currentSize = currentWord.size();
            std::cout << std::endl;
            std::cout << currentWord << " ";
        }
    }
    std::cout << std::endl;
}

Cleaner::~Cleaner() {
}