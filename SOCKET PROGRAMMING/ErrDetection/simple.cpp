#include <bits/stdc++.h>
using namespace std;

int countOnes(string s){
    int c=0;
    for(int i=0;i<s.size();i++){
        if(s[i]=='1'){
            c++;
        }
    }
    return c;
}


int main(){
    
    vector<string> ip(4);  // 4 * 8bits
    //ip={"11000001", "11001100", "00111100", "11111111"};
    
    for(int i=0;i<4;i++){
        cout << "Enter " << i+1 << "part: ";
        cin>>ip[i];
    }
    vector<string> codeword;
    
    for(int i=0;i<4;i++){
        int count = countOnes(ip[i]);
        string parityAdded = ip[i] + (count%2 ? '1':'0');
        codeword.push_back(parityAdded);
    }
    
    for(auto it: codeword){
        cout << it <<" ";
    }
    
    return 0;
}