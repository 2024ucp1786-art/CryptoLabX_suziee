#include <bits/stdc++.h>
using namespace std;

string prepare_plaintext(string text) {
    string s = "";

    for (char c : text) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            s += c;
        }
    }

    return s;
}

vector<string> create_digraphs(string s) {
    vector<string> d;

    for (int i = 0; i < s.size();) {
        if (i + 1 == s.size()) {
            d.push_back(string(1, s[i]) + "X");
            i++;
        }
        else if (s[i] == s[i + 1]) {
            d.push_back(string(1, s[i]) + "X");
            i++;
        }
        else {
            d.push_back(s.substr(i, 2));
            i += 2;
        }
    }

    return d;
}