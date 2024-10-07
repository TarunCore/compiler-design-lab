// Santhosh Kumar S P - 22BCE3084
#include <iostream>
#include <fstream>
#include <vector>

// Function to check if a string matches pattern 'a'
bool isPatternA(const std::string& str) {
    return str == "a";
}

// Function to check if a string matches pattern 'a*b'
bool isPatternAsteriskB(const std::string& str) {
    if (str.empty()) return false;
    int i = 0;
    while (i < str.size() && str[i] == 'a') {
        i++;
    }
    return i > 0 && i < str.size() && str[i] == 'b' && i == str.size() - 1;
}

// Function to check if a string matches pattern 'abb'
bool isPatternAbb(const std::string& str) {
    return str == "abb";
}

// Function to check if a string matches any of the patterns
bool isValidString(const std::string& str) {
    return isPatternA(str) || isPatternAsteriskB(str) || isPatternAbb(str);
}

int main() {
    std::ifstream inputFile("input3.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> results;

    while (std::getline(inputFile, line)) {
        if (isValidString(line)) {
            results.push_back(line + " : Valid");
        } else {
            results.push_back(line + " : Invalid");
        }
    }

    inputFile.close();

    for (const auto& result : results) {
        std::cout << result << std::endl;
    }

    return 0;
}