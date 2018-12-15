#include "Cleaner.h"

Cleaner::Cleaner() : validWords{}, frequencyPairs{}, largestWordSize{} {
}

void Cleaner::addWord(std::string potentialWord) {
    potentialWord.erase(0, potentialWord.find_first_not_of("\n\t\v\f\r"));
    potentialWord.erase(0, potentialWord.find_first_not_of("\"\'("));
    potentialWord.erase(potentialWord.find_last_not_of("\n\v\f\r\t") + 1);
    potentialWord.erase(potentialWord.find_last_not_of(",;.:?!\"\')") + 1);

    if ((potentialWord.size() > 3) && (0 == potentialWord.compare(potentialWord.size() - 2, 2, "\'s")))
        potentialWord.erase(potentialWord.size() - 2);

    if (potentialWord.size() < 3)
        return;
    if (potentialWord.at(0) == '-' || potentialWord.at(potentialWord.size() - 1) == '-')
        return;
    if (potentialWord.find("--") != std::string::npos)
        return;
    if (potentialWord.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-") != std::string::npos)
        return;

    std::transform(potentialWord.begin(), potentialWord.end(), potentialWord.begin(), ::tolower);

    if (potentialWord.size() > largestWordSize) {
        largestWordSize = potentialWord.size();
    }

    validWords.push_back(potentialWord);
}

void Cleaner::printOrdered(int const limit) {
    int currentSize{};

    auto wordPlacer = [&currentSize, &limit](std::string currentWord) {
        if ((currentSize + currentWord.size()) < limit) {
            currentSize += currentWord.size() + 1;
            std::cout << currentWord << " ";
        } else {
            currentSize = currentWord.size() + 1;
            std::cout << std::endl;
            std::cout << currentWord << " ";
        }
    };
    std::for_each(validWords.begin(), validWords.end(), wordPlacer);

    std::cout << std::endl;
}

int Cleaner::getLargestWordSize() {
    return largestWordSize;
}

void Cleaner::dynamicPrint(std::function<void(std::pair<std::string const&, int> const&)> const& printFunction) {
    std::for_each(frequencyPairs.begin(), frequencyPairs.end(), printFunction);
}

void Cleaner::sort(std::function<bool(std::pair<std::string const&, int> const& left, std::pair<std::string const&, int> const& right)> const& comparator) { 
    std::map<std::string, int> sortedValid{};

    auto updater = [&sortedValid](std::string word) {
        if (sortedValid.count(word) > 0) {
            sortedValid[word] = sortedValid[word] + 1;
        } else {
            sortedValid.emplace(word, 1);
        }
    };
    std::for_each(validWords.begin(), validWords.end(), updater);

    std::copy(sortedValid.begin(), sortedValid.end(), std::front_inserter(frequencyPairs));

    frequencyPairs.sort(comparator);
}

Cleaner::~Cleaner() {
}
