#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function declarations
int expression(const string &exp, size_t &index);
int term(const string &exp, size_t &index);
int factor(const string &exp, size_t &index);

// Function to evaluate an entire expression
int expression(const string &exp, size_t &index) {
    int value = term(exp, index);
    // Evaluate each term with + operator
    while (index < exp.size() && exp[index] == '+') {
        index++; // Skip the '+'
        cout << "Encountered '+', moving to next term" << endl;
        int nextValue = term(exp, index);
        cout << "Adding " << nextValue << " to " << value << endl;
        value += nextValue;
    }
    return value;
}

// Function to evaluate terms which may contain factors with *
int term(const string &exp, size_t &index) {
    int value = factor(exp, index);
    // Evaluate each factor with * operator
    while (index < exp.size() && exp[index] == '*') {
        index++; // Skip the '*'
        cout << "Encountered '*', moving to next factor" << endl;
        int nextValue = factor(exp, index);
        cout << "Multiplying " << value << " by " << nextValue << endl;
        value *= nextValue;
    }
    return value;
}

// Function to evaluate factors, which are digits in this case
int factor(const string &exp, size_t &index) {
    // Skip any whitespace
    while (index < exp.size() && isspace(exp[index])) {
        index++;
    }
    
    // Ensure current character is a digit
    if (index < exp.size() && isdigit(exp[index])) {
        int value = exp[index] - '0'; // Convert char to int
        cout << "Encountered digit: " << value << endl;
        index++;
        return value;
    }
    
    // Handle unexpected characters
    cout << "Unexpected character at index " << index << endl;
    return 0;
}

int main() {
    string expressionInput;
    cout << "Enter an arithmetic expression (e.g., 3+2*4): ";
    cin >> expressionInput;

    size_t index = 0;
    int result = expression(expressionInput, index);

    cout << "Final result: " << result << endl;
    return 0;
}
