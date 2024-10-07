#include <bits/stdc++.h>
#include <fstream>
using namespace std;

bool equalToComesNext(char c){
    return c=='+' || c=='-' || c=='*' || c=='+' || c=='>' || c=='<';
}

bool isOperator(char c){
    return c=='+' || c=='+' ||c=='-' ||c=='*' ||c=='/'|| c=='=' || c=='<' || c=='>';
}

template <typename T>
void printType(T s, string type){
    cout << s << " : " << type << endl;
}

void print2Char(char c, char d, string msg){
    cout << c <<d << " : " << msg << endl;
}

void process(string token){
    int n=token.size();
    for(int i=0;i<n;i++){
        char c = token[i];
        if(equalToComesNext(c)){
            if(i<n-1 && token[i+1]=='='){
                string p = "";p+=c;p+=token[i+1];
                printType(p, "Valid");
            }
            else if((c=='+' || c=='-') && i<n-1){
                if(token[i+1]==c){
                    print2Char(c,c, "Valid 2");
                }else{
                    print2Char(c, token[i+1], "Invalid");
                }
            }
            else{
                printType(c, "Valid Operator");
            }
        }else if(c=='='){
            if(i<n-1 && token[i+1]=='='){
                // printType("")
                print2Char(c,c,"Valid ==");
                i++;
            }
            if(i<n-1 && isOperator(token[i+1])){
                // printType("")
                print2Char(c,token[i+1],"Invalid ==");
                i++;
            }
            else{

            }
        }
    }
}

int main() {
    ifstream inputFile("file3.txt");
    string line;
    int lineNo=1;
    while(getline(inputFile, line)){
        stringstream ss(line);
        string token;
        while(getline(ss, token, ' ')){
            process(token);
        }
    }
    return 0;
}