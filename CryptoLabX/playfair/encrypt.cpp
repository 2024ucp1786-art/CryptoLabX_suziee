#include <bits/stdc++.h>
using namespace std;

pair<int,int> findPos(vector<vector<char>>& mat, char c) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (mat[i][j] == c)
                return {i, j};

    return {-1, -1};
}

string playfair_encrypt(vector<string> d, vector<vector<char>>& mat) {
    string cipher = "";

    for (auto p : d) {
        auto a = findPos(mat, p[0]);
        auto b = findPos(mat, p[1]);

        if (a.first == b.first) {
            cipher += mat[a.first][(a.second + 1) % 5];
            cipher += mat[b.first][(b.second + 1) % 5];
        }
        else if (a.second == b.second) {
            cipher += mat[(a.first + 1) % 5][a.second];
            cipher += mat[(b.first + 1) % 5][b.second];
        }
        else {
            cipher += mat[a.first][b.second];
            cipher += mat[b.first][a.second];
        }
    }

    return cipher;
}