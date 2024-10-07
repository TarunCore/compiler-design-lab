#include <bits/stdc++.h>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <cctype>

using namespace std;

bool isValidIdentifier(string token) {
    if (token.empty() || (!isalpha(token[0]) && token[0] != '_')) {
        return false;
    }
    for (int i = 1; i < token.length(); ++i) {
        if (!isalnum(token[i]) && token[i] != '_') {
            return false;
        }
    }
    return true;
}

bool isValidConstant(string token) {
    bool hasDecimalPoint = false;
    bool hasExponent = false;
    bool hasDigits = false;
    int i = 0;

    if (token[i] == '-' || token[i] == '+') {
        i++;
    }

    for (i; i < token.length(); ++i) {
        if (isdigit(token[i])) {
            hasDigits = true;
        } else if (token[i] == '.') {
            if (hasDecimalPoint || hasExponent) {
                return false;
            }
            hasDecimalPoint = true;
        } else if (token[i] == 'e' || token[i] == 'E') {
            if (hasExponent || !hasDigits) {
                return false;
            }
            hasExponent = true;
            hasDigits = false; 
            if (i + 1 < token.length() && (token[i + 1] == '+' || token[i + 1] == '-')) {
                i++;
            }
        } else {
            return false;
        }
    }
    return hasDigits;
}

void analyzeFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ' ')) {
            if (isValidIdentifier(token)) {
                cout << token << " is a valid identifier" << endl;
            } else if (isValidConstant(token)) {
                cout << token << " is a valid constant" << endl;
            } else {
                cout << token << " is invalid" << endl;
            }
        }
    }

    file.close();
}

int main() {
    string filename;
    cout << "Enter the filename: ";
    // cin >> filename;

    analyzeFile("file2.txt");

    return 0;
}
