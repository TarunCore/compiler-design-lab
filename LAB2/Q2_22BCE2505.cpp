#include <bits/stdc++.h>
#include <fstream>
using namespace std;

string getString(stack<char> st){
    string s="";
    while(!st.empty()){
        s+=st.top();
        st.pop();
    }
    reverse(s.begin(), s.end());
    return s;
}
void clearStack(stack<char> &st){
    stack<char> emptyStack;
    st.swap(emptyStack);
}

bool isNumber(string& token) {
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
bool isKeyword(string s){
    unordered_set<string> st={"print", "int", "if", "else", "elseif", "then", "endif", "float", "string"};
    return st.find(s)!=st.end();
}

bool isOperator(char c){
    return c=='+' || c=='+' ||c=='-' ||c=='*' ||c=='/'|| c=='=' || c=='<' || c=='>';
}

/**
 *  [ ] { ; whitespace , ( )
 */
bool isTerminating(char c){
    return c=='[' || c==']' || c=='{' || c=='}' || c==';' || c==' ' || c==',' || c=='(' || c==')' || c=='.';
}
template <typename T>
void printType(T s, string type){
    cout << s << " - " << type << endl;
}

void handleTermination(stack<char> &stack, string s, vector<int> &constants, vector<string> &identifiers, vector<string> &keywords, vector<char> &operators, vector<char> &delimiters){
    if(stack.empty()) return;
    clearStack(stack);
}

bool isEmpty(stack<char> &st){
    return st.empty();
}

set<string> validOperators = {
    "+", "-", "*", "/", "%", "++", "--", "&&", "||", "!",                 
    "==", "!=", ">", "<", ">=", "<=",        
    "&", "|", "^", "~", "<<", ">>",  
    "=", "+=", "-=", "*=", "/=", "%="
};

void process(string line){
    stack<char> stack;
    vector<int> constants;
    vector<string> identifiers;
    vector<char> operators;
    vector<char> delimiters;
    vector<string> keywords;
    bool commentStarts=false;
    string comment="";
    int n=line.size();
    for(int i=0;i<n;i++){
        char c=line[i]; bool isStackEmpty = isEmpty(stack);
        string s=getString(stack);
        if(isTerminating(c)){
            clearStack(stack);
            continue;
        }else if(isOperator(c)){
            string op="";
            int j=i;
            while(j<n && isOperator(line[j])){
                op+=line[j];
                j++;
            }
            i=j;
            if(validOperators.find(op)!=validOperators.end()){
                cout << op <<" valid operand\n";
            }else{
                cout << op << " Invalid operand\n";
            }
            handleTermination(stack, s, constants, identifiers, keywords, operators, delimiters);
        }else{
            stack.push(c);
        }
    }
    string s=getString(stack);
    handleTermination(stack, s, constants, identifiers, keywords, operators, delimiters);
}


int main() {
    ifstream inputFile("file2.txt");
    string line;
    int lineNo=1;
    while(getline(inputFile, line)){
        cout << "LINE " << lineNo <<endl;
        process(line);
        cout << "\n";
        lineNo++;
    }
    return 0;
}