#ifndef WORD_FREQUENCY_H
#define WORD_FREQUENCY_H

#include <string>
#include <map>
#include <list>
#include <vector>
#include <utility>
#include <cstddef>

class WordFrequency {
public:
    bool loadFromFile(const std::string& inputFile);
    void countWords();
    void sortWords();
    bool saveToCsv(const std::string& outputFile) const;
    int getTotalWords() const;
    std::size_t getUniqueWords() const;

private:
    std::list<std::string> lines_;
    std::map<std::string, int> wordFrequency_;
    std::vector<std::pair<std::string, int>> sortedWords_;
    int totalWords_ = 0;
};

#endif