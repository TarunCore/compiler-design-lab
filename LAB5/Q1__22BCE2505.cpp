#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Parser {
private:
    string expression;
    int index;
    char currentChar;
    int E_val;
    int T_val;
    int F_val;

    void nextChar() {
        if (index < expression.length()) {
            currentChar = expression[index++];
        } else {
            currentChar = '\0'; // End of input
        }
    }

    void E();
    void T();
    void F();

public:
    Parser(const string& expr) : expression(expr), index(0), currentChar(' '), E_val(0), T_val(0), F_val(0) {
        nextChar();
    }

    void parse() {
        E();
        if (currentChar != '\0') {
            cout << "Error: Unexpected character '" << currentChar << "'\n";
        } else {
            cout << "final value: " << E_val << endl;
        }
    }
};

void Parser::E() {
    T();
    E_val = T_val; // Initialize expression value with the term value
    cout << "E_val = " << E_val << endl;

    while (currentChar == '+') {
        nextChar();
        T();
        E_val += T_val; // Add the next term
        cout << "E_val = " << E_val << endl;
    }
}

void Parser::T() {
    F();
    T_val = F_val; // Initialize term value with the factor value
    cout << "T_val = " << T_val << endl;

    while (currentChar == '*') {
        nextChar();
        F();
        T_val *= F_val; // Multiply by the next factor
        cout << "T_val = " << T_val << endl;
    }
}

void Parser::F() {
    if (isdigit(currentChar)) {
        int digitVal = currentChar - '0'; // Convert character to integer
        F_val = digitVal;
        cout << "F_val = " << F_val << endl;
        nextChar();
    } else {
        cout << "Error: Invalid character '" << currentChar << "'\n";
    }
}

int main() {
    string userInput;
    cout << "Enter input: ";
    getline(cin, userInput);

    Parser calculator(userInput);
    calculator.parse();

    return 0;
}
