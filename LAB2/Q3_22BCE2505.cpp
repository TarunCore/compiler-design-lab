#include <bits/stdc++.h>
using namespace std;

bool checkPattern(string s){
    if (s == "a") {
        return true;
    }
    if (s[0] == 'a') {
        int i = 1;
        while (i < s.length() && s[i] == 'a') {
            i++;
        }
        if (i < s.length() && s[i] == 'b') {
            i++;
            while (i < s.length() && s[i] == 'b') {
                i++;
            }
            return i == s.length();
        }
    }
    return false;
}

int main(){
    ifstream inputFile("file3.txt");
    string line;
    while(getline(inputFile, line)){
        bool pat = checkPattern(line);
        if(pat){
            cout << line << " is valid pattern\n"; 
        }else{
            cout << line << " is invalid\n"; 
        }
    }

    return 0;
}