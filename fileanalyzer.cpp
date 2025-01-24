#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

// class encapsulates the logic for reading, processing, and displaying word occurrences
class WordCounter {
private:
    std::map<std::string, int> wordMap; // Data structure to store word counts

    // Cleans and normalizes a word: removes non-alphanumeric characters and converts to lowercase
    std::string cleanWord(const std::string &word) {
        std::string cleanedWord;
        for (char c : word)
            if (std::isalnum(c)) cleanedWord += std::tolower(c); // Keep only alphanumeric characters
        return cleanedWord;
    }

public:
    // Reads the input file and counts the occurrences of each word
    void processFile(const std::string &filename) {
        std::ifstream file(filename); // Open the file for reading
        if (!file.is_open()) { // Check if the file opened successfully
            std::cerr << "Error: Unable to open file \"" << filename << "\"." << std::endl;
            return;
        }
        std::string line, word;
        // Read the file line by line
        while (std::getline(file, line)) {
            std::istringstream stream(line); // Create a string stream for processing each line
            // Extract words from the line
            while (stream >> word) {
                word = cleanWord(word); // Clean and normalize the word
                if (!word.empty()) wordMap[word]++; // Increment word count if it's valid
            }
        }
        file.close(); // Close the file after reading
    }

    // Displays word counts and optionally writes them to an output file
    void displayResults(bool saveToFile, const std::string &outputFilename = "") const {
        std::ofstream outFile;
        if (saveToFile) { // Open the output file if the user wants to save results
            outFile.open(outputFilename);
            if (!outFile.is_open()) { // Check if the output file opened successfully
                std::cerr << "Error: Unable to open output file \"" << outputFilename << "\"." << std::endl;
                return;
            }
        }

        if (wordMap.empty()) { // Handle case where no words are found in the file
            std::cout << "No words found in the file." << std::endl;
            if (saveToFile) outFile << "No words found in the file." << std::endl;
            return;
        }

        // Sort the words by frequency in descending order
        std::vector<std::pair<std::string, int>> sortedWords(wordMap.begin(), wordMap.end());
        std::sort(sortedWords.begin(), sortedWords.end(), [](const auto &a, const auto &b) {
            return b.second > a.second; // Sort by frequency (highest first)
        });

        std::cout << "Word occurrences (sorted by frequency):" << std::endl;
        if (saveToFile) outFile << "Word occurrences (sorted by frequency):" << std::endl;

        // Display each word and its frequency
        for (const auto &pair : sortedWords) {
            std::cout << pair.first << ": " << pair.second << std::endl;
            if (saveToFile) outFile << pair.first << ": " << pair.second << std::endl;
        }

        if (saveToFile) outFile.close(); // Close the output file after writing
    }
};

int main() {
    WordCounter counter; // Create an instance of the WordCounter class
    std::string inputFilename, outputFilename; // Variables for filenames
    char saveToFileChoice; // Variable to store user's choice for saving results

    // Prompt the user to enter the name of the text file to analyze
    std::cout << "Enter the name of the text file to analyze: ";
    std::cin >> inputFilename;

    // Ask the user if they want to save the results to a file
    std::cout << "Do you want to save the results to a file? (y/n): ";
    std::cin >> saveToFileChoice;

    // Check if the user chose to save the results
    bool saveToFile = (saveToFileChoice == 'y' || saveToFileChoice == 'Y');

    // If the user wants to save the results, ask for the output file name
    if (saveToFile) {
        std::cout << "Enter the name of the output file to save results: ";
        std::cin >> outputFilename;
    }

    // Process the input file to count word occurrences
    counter.processFile(inputFilename);

    // Display the results (and save to a file if the user chose to)
    counter.displayResults(saveToFile, outputFilename);

    return 0; // Exit the program
}
