#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

// Encapsulating the word counting functionality
class WordCounter {
private:
    std::map<std::string, int> wordMap; // Data structure to store word counts

    // Clean and normalize words
    std::string cleanWord(const std::string &word) {
        std::string cleanedWord;
        for (char c : word) {
            if (std::isalnum(c)) {
                cleanedWord += std::tolower(c);
            }
        }
        return cleanedWord;
    }

public:
    // Process the file and count words
    void processFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file \"" << filename << "\"." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream stream(line);
            std::string word;
            while (stream >> word) {
                word = cleanWord(word);
                if (!word.empty()) {
                    wordMap[word]++;
                }
            }
        }
        file.close();
    }

    // Prints out word counts
    void displayResults() const {
        std::cout << "Word occurrences:" << std::endl;
        for (const auto &pair : wordMap) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};

int main() {
    WordCounter counter;
    std::string filename;
    // Prompts the user for a file name
    std::cout << "Enter the name of the text file to analyze: ";
    std::cin >> filename;
    // Calls the Process Function
    counter.processFile(filename);
    // Calls the Results Funtion
    counter.displayResults();

    return 0;
}
