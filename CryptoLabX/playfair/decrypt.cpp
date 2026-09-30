#include <bits/stdc++.h>


using namespace std;


string playfair_decrypt(string cipher, vector<vector<char>>& mat) {
    string plain = "";

    for (int i = 0; i < cipher.size(); i += 2) {
        auto a = findPos(mat, cipher[i]);
        auto b = findPos(mat, cipher[i + 1]);

        if (a.first == b.first) {
            plain += mat[a.first][(a.second + 4) % 5];
            plain += mat[b.first][(b.second + 4) % 5];
        }
        else if (a.second == b.second) {
            plain += mat[(a.first + 4) % 5][a.second];
            plain += mat[(b.first + 4) % 5][b.second];
        }
        else {
            plain += mat[a.first][b.second];
            plain += mat[b.first][a.second];
        }
    }

    return plain;
}
