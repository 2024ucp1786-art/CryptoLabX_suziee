#include <bits/stdc++.h>
using namespace std;

bool verify(string cipher, string decrypted,
            vector<vector<char>>& mat) {

    // decrypted -> digraphs
    vector<string> d;

    for (int i = 0; i < decrypted.size(); i += 2)
        d.push_back(decrypted.substr(i, 2));

    string result = "";

    for (auto p : d) {
        pair<int,int> a, b;

        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++) {
                if (mat[i][j] == p[0]) a = {i,j};
                if (mat[i][j] == p[1]) b = {i,j};
            }

        if (a.first == b.first) {
            result += mat[a.first][(a.second + 1) % 5];
            result += mat[b.first][(b.second + 1) % 5];
        }
        else if (a.second == b.second) {
            result += mat[(a.first + 1) % 5][a.second];
            result += mat[(b.first + 1) % 5][b.second];
        }
        else {
            result += mat[a.first][b.second];
            result += mat[b.first][a.second];
        }
    }

    return result == cipher;
}