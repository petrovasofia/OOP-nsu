#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>

#include "WordFrequency.h"

bool WordFrequency::loadFromFile(const std::string& inputFile) {
    std::ifstream textFile(inputFile);
    if (!textFile.is_open()) {
        return false;
    }

    lines_.clear();
    std::string line;
    while (std::getline(textFile, line)) {
        lines_.push_back(line);
    }
    textFile.close();
    return true;
}

void WordFrequency::countWords() {
    wordFrequency_.clear();
    totalWords_ = 0;

    for (const std::string& currentLine : lines_) {
        std::string currentWord;
        for (char ch : currentLine) {
            if (std::isalnum(static_cast<unsigned char>(ch))) {
                currentWord += ch;
            } else if (!currentWord.empty()) {
                wordFrequency_[currentWord]++;
                currentWord.clear();
            }
        }
        if (!currentWord.empty()) {
            wordFrequency_[currentWord]++;
        }
    }

    for (const auto& pair : wordFrequency_) {
        totalWords_ += pair.second;
    }
}

void WordFrequency::sortWords() {
    sortedWords_.assign(wordFrequency_.begin(), wordFrequency_.end());
    std::sort(sortedWords_.begin(), sortedWords_.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });
}

bool WordFrequency::saveToCsv(const std::string& outputFile) const {
    std::ofstream CSVFile(outputFile);
    if (!CSVFile.is_open()) {
        return false;
    }

    CSVFile << "Word,Frequency,Frequency (%)" << std::endl;
    for (const auto& pair : sortedWords_) {
        double percent = totalWords_ > 0 ? 100.0 * pair.second / totalWords_ : 0.0;
        CSVFile << pair.first << "," << pair.second << "," << percent << std::endl;
    }
    CSVFile.close();
    return true;
}

int WordFrequency::getTotalWords() const {
    return totalWords_;
}

std::size_t WordFrequency::getUniqueWords() const {
    return wordFrequency_.size();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0]
             << " <input.txt> <output.csv>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    WordFrequency wf;

    if (!wf.loadFromFile(inputFile)) {
        std::cerr << "Failed to open " << inputFile << std::endl;
        return 1;
    }

    wf.countWords();
    wf.sortWords();

    if (!wf.saveToCsv(outputFile)) {
        std::cerr << "Failed to create " << outputFile << std::endl;
        return 1;
    }

    std::cout << "Total words: " << wf.getTotalWords()
              << ", unique: " << wf.getUniqueWords() << std::endl;
    return 0;
}
