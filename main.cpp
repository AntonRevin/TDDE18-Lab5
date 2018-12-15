#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include "Cleaner.h"

using namespace std;

void printError(string const description) {
    cerr << "\033[1;31m" << description << "\033[0m" << endl;
    cerr << "Usage: ./a.out FILE [-a] [-f] [-o N]" << endl;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printError("ERROR: No arguments given.");
        return -1;
    }

    /*
        Retreive argument list
    */
    string fileName{};
    string outputFormat{};
    int charLimit{};

    try {
        fileName = argv[1];
        outputFormat = argv[2];

        if ((outputFormat == "-o") && (argc = 4)) {
            charLimit = stoi(argv[3]);
            if (charLimit < 4) {
                printError("ERROR: Words are defined as containing 3 or more characters.");
                return -1;
            }
        } else if (outputFormat == "-o") {
            printError("ERROR: Second argument missing or invalid.");
            return -1;
        }
    } catch (const std::exception& e) {
        printError("ERROR: Incorrect argument list.");
        return -1;
    }

    /*
        Open file and pipe to cleaner
    */
    ifstream fileStream{};
    fileStream.open(fileName);
    if (!fileStream.is_open()) {
        printError("ERROR: Could not open the file.");
        return -1;
    }

    Cleaner cleaner{};

    istream_iterator<string> iter(fileStream);
    istream_iterator<string> eof;

    list<string> potentialWords;

    copy(iter, eof, back_inserter(potentialWords));

    auto cleanerAdder = [&cleaner](string potentialWord) {
        cleaner.addWord(potentialWord);
    };
    for_each(potentialWords.begin(), potentialWords.end(), cleanerAdder);

    fileStream.close();

    /*
        Select output format
    */
    int maxWidth{cleaner.getLargestWordSize()};

    auto aComparator = [](pair<string, int> left, pair<string, int> right) {
        return left.first.compare(right.first) < 0;
    };
    auto aPrinter = [maxWidth](pair<string, int> currentPair) {
        cout << left << setw(maxWidth) << currentPair.first << " " << currentPair.second << endl;
    };
    auto fComparator = [](pair<string, int> left, pair<string, int> right) {
        return left.second >= right.second;
    };
    auto fPrinter = [maxWidth](pair<string, int> currentPair) {
        cout << right << setw(maxWidth) << currentPair.first << " " << currentPair.second << endl;
    };

    switch (outputFormat[1]) {
        case 'a':
            cleaner.sort(aComparator);
            cleaner.dynamicPrint(aPrinter);
            break;

        case 'f':
            cleaner.sort(fComparator);
            cleaner.dynamicPrint(fPrinter);
            break;

        case 'o':
            cleaner.printOrdered(charLimit);
            break;

        default:
            printError("ERROR: Incorrect argument list.");
            return -1;
            break;
    }

    return 1;
}