#include <bits/stdc++.h>
using namespace std;


int countBits(string bits){
    int count=0;
    for(int i=0;i<bits.size();i++){
        if(bits[i]=='1'){
            count++;
        }
    }
    return count;
}

void printRow(string s, int parity){
    for(char &cc:s){
        cout << cc << " ";
    }
    cout << " ";
    cout << parity << endl;
}

int main(){
    
    
    vector<string> ip(4);
    //ip={"10001000", "11110000","00110011","10101010"};
    // either hardcoding or taking input in below
    
    for(int i=0;i<4;i++){
        cout << "Enter " << i+1 <<" part: ";
        cin>>ip[i];
    }
    vector<int> rowParity, colParity;
    
    vector<string> output;
    
    
    for(int i=0;i<4;i++){
        int c=0;
        for(int j=0;j<8;j++){
            if(ip[i][j]=='1') c++;
        }
        int par = c%2?1:0;
        char parc = c%2?'1':'0';
        printRow(ip[i], par);
        output.push_back(ip[i]+parc);
        rowParity.push_back(par);
    }
    for(int i=0;i<8;i++){
        int c=0;
        for(int j=0;j<4;j++){
            if(ip[j][i]=='1') c++;
        }
        colParity.push_back(c%2?1:0);
    }
    int dparity=0;
    for(int i=0;i<rowParity.size();i++) dparity+=rowParity[i];
    dparity=dparity%2;
    colParity.push_back(dparity);
    
    cout << endl;
    string lastParity = "";
    for(auto &it: colParity){
        cout << it << " ";
        if(it==1){
            lastParity+='1';
        }else{
            lastParity+='0';
        }
    }
    cout << "\nOutput:\n";
    output.push_back(lastParity);
    for(auto &s:output){
        cout << s <<" ";
    }
    //cout << " " <<dparity;
    
    
    return 0;
}