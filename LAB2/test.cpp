#include <bits/stdc++.h>
using namespace std;

bool isNumber(string s) {
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

int main() 
{
  string s="44";
    count << isNumber(s);
    cout << "Hello, World!";
    return 0;
}