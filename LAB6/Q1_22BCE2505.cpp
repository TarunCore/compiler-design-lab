#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

// AST Node structure
struct ASTNode {
    string value;
    ASTNode* left;
    ASTNode* right;

    ASTNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

// TAC Instruction structure
struct TACInstruction {
    string result;
    string op;
    string arg1;
    string arg2;

    TACInstruction(string res, string operation, string a1, string a2)
        : result(res), op(operation), arg1(a1), arg2(a2) {}
};

class Parser {
public:
    string expression;
    int index;
    char currentChar;
    int tempVarCounter;
    vector<TACInstruction> tacInstructions;

    void nextChar() {
        if (index < expression.length()) {
            currentChar = expression[index++];
        } else {
            currentChar = '\0'; // End of input
        }
    }

    ASTNode* E();
    ASTNode* T();
    ASTNode* F();
    void generateTAC(ASTNode* node);

public:
    Parser(const string& expr) : expression(expr), index(0), currentChar(' '), tempVarCounter(0) {
        nextChar();
    }

    ASTNode* parse() {
        ASTNode* root = E();
        if (currentChar != '\0') {
            cout << "Error: Unexpected character '" << currentChar << "'\n";
        }
        return root;
    }

    void printTAC() {
        for (const auto& instr : tacInstructions) {
            cout << instr.result << " = " << instr.arg1 << " " << instr.op << " " << instr.arg2 << endl;
        }
    }

    string newTempVar() {
        return "t" + to_string(tempVarCounter++);
    }
};

// Recursive Descent Parsing for Expression E -> T (+|- T)*
ASTNode* Parser::E() {
    ASTNode* node = T();

    while (currentChar == '+' || currentChar == '-') {
        char op = currentChar;
        nextChar();
        ASTNode* rightNode = T();
        ASTNode* newNode = new ASTNode(string(1, op));
        newNode->left = node;
        newNode->right = rightNode;
        node = newNode;
    }

    return node;
}

// Term Parsing: T -> F (*|/ F)*
ASTNode* Parser::T() {
    ASTNode* node = F();

    while (currentChar == '*' || currentChar == '/') {
        char op = currentChar;
        nextChar();
        ASTNode* rightNode = F();
        ASTNode* newNode = new ASTNode(string(1, op));
        newNode->left = node;
        newNode->right = rightNode;
        node = newNode;
    }

    return node;
}

// Factor Parsing: F -> number
ASTNode* Parser::F() {
    if (isdigit(currentChar)) {
        string numStr;
        while (isdigit(currentChar)) {
            numStr += currentChar;
            nextChar();
        }
        return new ASTNode(numStr);
    } else {
        cout << "Error: Invalid character '" << currentChar << "'\n";
        return nullptr;
    }
}

// TAC Generation
void Parser::generateTAC(ASTNode* node) {
    if (!node || (!node->left && !node->right)) return;

    // Post-order traversal to generate TAC
    generateTAC(node->left);
    generateTAC(node->right);

    if (node->left && node->right) {
        string tempVar = newTempVar();
        tacInstructions.push_back(TACInstruction(tempVar, node->value, node->left->value, node->right->value));
        node->value = tempVar; // Replace node value with temp variable for further use
    }
}

// AST Printing (Helper Function)
void printAST(ASTNode* node, int level = 0) {
    if (node == nullptr) return;
    
    for (int i = 0; i < level; i++) cout << "  ";
    cout << node->value << endl;

    printAST(node->left, level + 1);
    printAST(node->right, level + 1);
}

int main() {
    string userInput;
    cout << "Enter input expression: ";
    getline(cin, userInput);

    Parser parser(userInput);

    // Parse and generate AST
    ASTNode* astRoot = parser.parse();
    
    if (astRoot) {
        cout << "\nAbstract Syntax Tree (AST):\n";
        printAST(astRoot);

        // Generate and print Three Address Code (TAC)
        parser.generateTAC(astRoot);
        cout << "\nThree Address Code (TAC):\n";
        parser.printTAC();
    }

    return 0;
}
