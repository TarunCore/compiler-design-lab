#include <bits/stdc++.h>
#include <fstream>
using namespace std;

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
bool isNumber(string& s) {
    try {
        size_t pos;
        stoi(s, &pos);
        return pos == s.length();
    } catch (invalid_argument& e) {
        return false; // invald number
    } catch (out_of_range& e) {
        return false; // out of range int
    }
}
bool isKeyword(string s){
    unordered_set<string> st={"print", "int", "if", "else", "elseif", "then", "endif"};
    return st.find(s)!=st.end();
}

bool isOperator(char c){
    return c=='+' || c=='+' ||c=='-' ||c=='*' ||c=='/'|| c=='=' || c=='<' || c=='>';
}

/**
 *  [ ] { ; whitespace , ( )
 */
bool isTerminating(char c){
    return c=='[' || c==']' || c=='{' || c=='}' || c==';' || c==' ' || c==',' || c=='(' || c==')';
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
    }else{
        identifiers.push_back(s);
        printType(s,"Identifier");
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
            if(!isWhiteSpace(c)){
                delimiters.push_back(c);
                printType(c, "Delimiter");
            }
            if(isWhiteSpace(c) || c==','){
                handleTermination(stack, s, constants, identifiers, keywords, operators, delimiters);
            }
            else if(c=='['){ // mostly HANDLES IDENTIFIERS
                identifiers.push_back(s);
                printType(s,"Identifier");
                clearStack(stack);
            }
            else if(c==']'){
                if(isNumber(s)){
                    int num = stoi(s);
                    constants.push_back(num);
                    printType(num,"Constant");
                    clearStack(stack);
                }else{
                    // cout << "Error processing []";
                }

            }else if(c=='{'){
                if(isStackEmpty) continue;
                if(isKeyword(s)){
                    keywords.push_back(s);
                    printType(s,"Keyword");
                }else{
                    // printMsg("Error processing {");
                }
            }else if(c==';'){ // contant, 
                if(!isStackEmpty){  // print(t1);
                    if(!isNumber(s)){  // int t2;
                        identifiers.push_back(s);
                        printType(s,"Identifier");
                    }else{ // =45;
                        int num=stoi(s);
                        constants.push_back(num);
                        printType(num,"Constant");
                    }
                    clearStack(stack);
                }
            }else if(c=='('){
                if(isStackEmpty) continue;
                if(isKeyword(s)){
                    keywords.push_back(s);
                    printType(s,"Keyword");
                    clearStack(stack);
                }else{
                    // printMsg("Error processing (");
                }
            }else if(c==')'){
                if(isStackEmpty) continue;
                if(!isNumber(s)){ //print(t2-t3);
                    identifiers.push_back(s);
                    printType(s,"Identifier");
                }else{ // print(t1-1)
                    int num=stoi(s);
                    constants.push_back(num);
                    printType(num,"Constant");
                }
                clearStack(stack);
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
    ifstream inputFile("code.txt");
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