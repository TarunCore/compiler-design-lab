#include <bits/stdc++.h>
#include <iomanip> 

using namespace std;

map<string, vector<string>> grammar = {
    {"E", {"T E'"}},
    {"E'", {"+ T E'", "#"}},
    {"T", {"F T'"}},
    {"T'", {"* F T'", "#"}},
    {"F", {"( E )", "id"}}
};

map<pair<string, string>, string> parseTable = {
    {{"E", "id"}, "T E'"},
    {{"E", "("}, "T E'"},
    {{"E'", "+"}, "+ T E'"},
    {{"E'", ")"}, "#"},
    {{"E'", "$"}, "#"},
    {{"T", "id"}, "F T'"},
    {{"T", "("}, "F T'"},
    {{"T'", "*"}, "* F T'"},
    {{"T'", "+"}, "#"},
    {{"T'", ")"}, "#"},
    {{"T'", "$"}, "#"},
    {{"F", "id"}, "id"},
    {{"F", "("}, "( E )"}
};

void display(stack<string> st, vector<string> buffer, string action) {
    string sStack = "";
    string sBuffer = "";

    stack<string> stCopy = st;
    while (!stCopy.empty()) {
        sStack = stCopy.top() + " " + sStack;
        stCopy.pop();
    }

    for (auto it : buffer)
        sBuffer += it + " ";

    cout << setw(35) << left << sBuffer
         << setw(35) << left << sStack
         << setw(25) << left << action << endl;
}

bool LL1Parser(string input) {
    stack<string> st;
    vector<string> buffer;

    st.push("$");
    st.push("E");

    string token = "";
    for (char c : input) {
        if (c != ' ') token += c;
        else {
            buffer.push_back(token);
            token = "";
        }
    }
    buffer.push_back(token);
    buffer.push_back("$");

    cout << setw(35) << left << "Buffer"
         << setw(35) << left << "Stack"
         << setw(25) << left << "Action" << endl;
    display(st, buffer, "Start Parsing");

    while (!st.empty()) {
        string topStack = st.top();
        string frontBuffer = buffer.front();

        if (topStack == frontBuffer) {
            st.pop();
            buffer.erase(buffer.begin());
            display(st, buffer, "Matched " + topStack);
        }
        else if (grammar.find(topStack) != grammar.end()) {
            st.pop();

            string production = parseTable[{topStack, frontBuffer}];
            if (production == "") return false;

            vector<string> toPush;
            string temp = "";
            for (char c : production) {
                if (c != ' ') temp += c;
                else {
                    toPush.push_back(temp);
                    temp = "";
                }
            }
            if (temp != "") toPush.push_back(temp);

            reverse(toPush.begin(), toPush.end());
            for (auto symbol : toPush) {
                if (symbol != "#") st.push(symbol);  
            }

            display(st, buffer, "Apply " + topStack + " -> " + production);
        }
        else return false;  
    }

    return (st.empty() && buffer.empty());
}

int main() {
    string input = "( id * id ) + id * ( id + id )";

    if (LL1Parser(input)) {
        cout << "Input string is valid accoding to grammar." << endl;
    } else {
        cout << "Invalid" << endl;
    }

    return 0;
}
