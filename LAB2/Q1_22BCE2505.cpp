#include <bits/stdc++.h>
#include <fstream>
using namespace std;

bool isValidIdentifier(string token) {
    if (token.empty()) {
        return false;
    }
    // checking number
    if(!isalpha(token[0]) && token[0] != '_'){
        return false;
    }
    for (int i = 1; i < token.length(); ++i) {
        if (!isalnum(token[i]) && token[i] != '_') {
            return false;
        }
    }
    return true;
}

bool isInteger(string s) {
    for (int i = 0; i < s.length(); ++i) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

template <typename T>
void printVector(vector<T> &v){
    for(auto it: v){
        cout << it << " ";
    }
    cout << endl;
}
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
bool isWhiteSpace(char c){
    return c==' ';
}
void printMsg(string msg){
    cout << msg << endl;
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
    if(isNumber(s)){
        int num = stoi(s);
        constants.push_back(num);
        printType(num,"Constant");
    }else if(isKeyword(s)){
        keywords.push_back(s);
        printType(s,"Keyword");
    }else if(isValidIdentifier(s)){
        identifiers.push_back(s);
        printType(s,"Identifier");
    }else{
        printType(s, "Invalid token");
    }
    clearStack(stack);
}

bool isEmpty(stack<char> &st){
    return st.empty();
}

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
        if(!commentStarts &&  c=='/' && i<n-1 && line[i+1]=='*'){
            commentStarts=true;
            i+=1;
            continue;
        }
        if(commentStarts){
            if(c=='*' && i<n-1 && line[i+1]=='/'){
                commentStarts=false;
                printMsg(comment);
                i++;
            }
            comment+=c;
            continue;
        }
        if(isTerminating(c)){
            //cout << c << " ll ";
            if(!isWhiteSpace(c)){
                delimiters.push_back(c);
            }
            if(isWhiteSpace(c) || c==','){
                handleTermination(stack, s, constants, identifiers, keywords, operators, delimiters);
            }
            else if(c=='['){ // mostly HANDLES IDENTIFIERS
                if(isValidIdentifier(s)){
                    identifiers.push_back(s);
                    printType(s,"Identifier");
                }else{
                    printType(s, "Invalid token");
                }
                clearStack(stack);
            }
            else if(c==']'){
                if(isNumber(s)){
                    clearStack(stack);
                    if(isInteger(s)){ // float passed in to [index]
                        int num = stoi(s);
                        constants.push_back(num);
                        printType(num,"Constant");
                    }else{
                        cout << s<< " - Float passed to []\n";
                    }
                    
                }

            }else if(c=='{'){
                if(isStackEmpty) continue;
                if(isKeyword(s)){
                    keywords.push_back(s);
                }
            }else if(c==';'){ // contant, 
                if(!isStackEmpty){  // print(t1);
                    if(isNumber(s)){ // =45; 
                        // int num=stoi(s);
                        // constants.push_back(num);
                        printType(s,"Constant");
                    }else if(isValidIdentifier(s)){  // int t2;
                        identifiers.push_back(s);
                        printType(s,"Identifier");
                    }else{
                        printType(s, "Invalid token");
                    }
                    clearStack(stack);
                }
            }else if(c=='('){
                if(isStackEmpty) continue;
                if(isKeyword(s)){
                    keywords.push_back(s);
                    clearStack(stack);
                }
                
            }else if(c==')'){
                if(isStackEmpty) continue;
                if(isValidIdentifier(s)){ //print(t2-t3);
                    identifiers.push_back(s);
                    printType(s,"Identifier");
                }
                else if(isNumber(s)){ // print(t1-1)
                    printType(s,"Constant");
                }
                else{
                    printType(s, "Invalid token");
                }
                clearStack(stack);
            }else if(c=='.'){
                stack.push(c);
            }
        }else if(isOperator(c)){
            operators.push_back(c);
            handleTermination(stack, s, constants, identifiers, keywords, operators, delimiters);
        }else{
            stack.push(c);
        }
    }
    string s=getString(stack);
    handleTermination(stack, s, constants, identifiers, keywords, operators, delimiters);
}


int main() {
    ifstream inputFile("file1.txt");
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