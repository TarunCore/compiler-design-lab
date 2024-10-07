#include <bits/stdc++.h>
#include <fstream>
using namespace std;

void printMsg(string msg){
    cout << msg << endl;
}

void process(string line){
    stack<char> stack;
    bool commentStarts=false;
    string comment="";
    int n=line.size();
    for(int i=0;i<n;i++){
        char c=line[i];
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
    }

}


int main() {
    ifstream inputFile("checkComment.txt");
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