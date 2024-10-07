#include <bits/stdc++.h>
using namespace std;

string xorNumbers(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string mode2(string dividend, string divisor) {
    int pick = divisor.length();
    string temp = dividend.substr(0, pick);
    while (pick < dividend.length()) {
        if (temp[0] == '1') {
            temp = xorNumbers(divisor, temp) + dividend[pick];
        } else {
            temp = xorNumbers(string(pick, '0'), temp) + dividend[pick];
        }
        pick += 1;
    }
if (temp[0] == '1') {
        temp = xorNumbers(divisor, temp);
    } else {
        temp = xorNumbers(string(pick, '0'), temp);
    }
    return temp;
}

string appendZeroes(string data, int n) {
    return data + string(n, '0');
}
int main() {
    string data, divisor, crc, rem, codeword;
cout << "Enter the data word ";
    cin >> data;
    cout << "Enter dviisor ";
    cin >> divisor;
    int m = data.length();
    int n = divisor.length();
    string augDataa = appendZeroes(data, n - 1);

    crc = mode2(augDataa, divisor);

    codeword = data + crc;cout << "senders:\n";
    cout << "Data word: " << data << endl;
    cout << "augDataa word: " << augDataa << endl;
    cout << "CRC:\n" << crc << endl;
    cout << "Receiver:\n";
    cout << "Code word: " << codeword << endl;
rem = mode2(codeword, divisor);
    cout << "rem: " << rem << endl;

    if (rem.find('1') != string::npos) {
        cout << "Error detected";
    } else {
        cout << "No error detectd";
    }
return 0;
}