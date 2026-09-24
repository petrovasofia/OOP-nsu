#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

void analyzeText(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream textFile(inputFile);
    if (!textFile.is_open()) {
        std::cerr << "Could not open input file: " << inputFile << std::endl;
        return;
    }

    std::list<std::string> lines;
    std::string line;

    while (std::getline(textFile, line)) {
        lines.push_back(line);
    }
    textFile.close();

    std::map<std::string, int> wordFrequency;
    for (const std::string& currentLine : lines) {
        std::string currentWord;
        for (char ch : currentLine) {
            if (std::isalnum((unsigned char)ch)) {
                currentWord += ch;
            } else if (!currentWord.empty()) {
                wordFrequency[currentWord]++;
                currentWord.clear();
            }
        }
        if (!currentWord.empty()) {
            wordFrequency[currentWord]++;
        }
    }

    int countOfWords = 0;
    for (const auto& pair : wordFrequency) {
        countOfWords += pair.second;
    }

    std::vector<std::pair<std::string, int>> sortedWords(wordFrequency.begin(), wordFrequency.end());
    std::sort(sortedWords.begin(), sortedWords.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });

    std::ofstream CSVFile(outputFile);
    if (!CSVFile.is_open()) {
        std::cerr << "Could not open output file: " << outputFile << std::endl;
        return;
    }

    CSVFile << "Word,Frequency,Frequency (%)" << std::endl;
    for (const auto& pair : sortedWords) {
        double percent = countOfWords > 0 ? 100.0 * pair.second / countOfWords : 0.0;
        CSVFile << pair.first << "," << pair.second << "," << percent << std::endl;
    }
    CSVFile.close();

    std::cout << "Total words: " << countOfWords << ", unique words: " << wordFrequency.size() << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    analyzeText(inputFile, outputFile);

    return 0;
}