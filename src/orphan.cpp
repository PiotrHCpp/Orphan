#include "orphan.hpp"

#include <string>
#include <sstream>
#include <queue>

void removeFrontSpaces(std::string& line) {
    if(!line.size()) return;
    auto endOfWhiteSpaces = line.find_first_not_of(' ', 0);
    if(endOfWhiteSpaces != std::string::npos) {
        line.erase(0, endOfWhiteSpaces);
    }
}

void removeSpacesOnTheEnd(std::string& line) {
    if(!line.size()) return;
    auto whiteSpacesBegin = line.find_last_not_of(' ');
    if(whiteSpacesBegin != std::string::npos) {
        line.erase(whiteSpacesBegin + 1);
    }
}

void removeMultipleSpaces(std::string& line) {
    if(!line.size()) return;
    size_t doubleSpaceCharPosition = 0;
    size_t spaceCounter = 0;

    while(doubleSpaceCharPosition != std::string::npos) {
        spaceCounter = 0;
        doubleSpaceCharPosition = line.find("  ", 0);
        while(line[++spaceCounter + doubleSpaceCharPosition] == ' ');
        line.erase(doubleSpaceCharPosition + 1, spaceCounter - 1);
        doubleSpaceCharPosition = line.find("  ", 0);
    }
}

void insertHardspacesAfterOrphans(std::string& line) {
    if(!line.size()) return;
    std::stringstream lineStream(line);
    std::queue<std::string> orphans;

    while(lineStream) {
        std::string word;
        lineStream >> word;
        if(word.size() == 1) orphans.push(word);
    }
    const size_t orphanCount = orphans.size();

    for(size_t it = 0; it < orphanCount; ++it) {
        std::string toFind = " ";
        toFind.append(orphans.front() + ' ');
        orphans.pop();
        auto found = line.find(toFind);
        if(found != std::string::npos) {
            line[found + 2] = '~';
        }
    }
}

void insertHardSpacesAfterSurnames(std::string& line) {
    if(!line.size()) return;
    const size_t lineSize = line.size();
    size_t currentSpaceChar{0};
    size_t previousSpaceChar{0};

    while(currentSpaceChar != std::string::npos) {
        currentSpaceChar = line.find(' ', ++previousSpaceChar);
        previousSpaceChar = currentSpaceChar;
        if((currentSpaceChar + 2) < lineSize &&
            ::isupper(line[currentSpaceChar + 1]) &&
            line[currentSpaceChar + 2] == '.')
        {
            line[currentSpaceChar] = '~';
        }
    }
}
