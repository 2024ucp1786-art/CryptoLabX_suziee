#include <bits/stdc++.h>
#include "prep.cpp"
#include "encrypt.cpp"
#include "decrypt.cpp"
#include "verify.cpp"
using namespace std;

string prepare_plaintext(string);
vector<string> create_digraphs(string);

string playfair_encrypt(vector<string>, vector<vector<char>>&);
string playfair_decrypt(string, vector<vector<char>>&);
bool verify(string, string, vector<vector<char>>&);

vector<vector<char>> generate_key_matrix(string key) {
    vector<vector<char>> mat(5, vector<char>(5));
    string s = "";

    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';

        if (isalpha(c) && s.find(c) == string::npos)
            s += c;
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;

        if (s.find(c) == string::npos)
            s += c;
    }

    for (int i = 0; i < 25; i++)
        mat[i / 5][i % 5] = s[i];

    return mat;
}

int main() {
    string key = "MONARCHY";
    string plaintext = "INSTRUMENTS";

    auto mat = generate_key_matrix(key);

    cout << "Key Matrix:\n";
    for (auto row : mat) {
        for (char c : row)
            cout << c << " ";
        cout << "\n";
    }

    string prepared = prepare_plaintext(plaintext);
    vector<string> digraphs = create_digraphs(prepared);

    cout << "\nPrepared Digraphs:\n";
    for (auto x : digraphs)
        cout << x << " ";

    string cipher = playfair_encrypt(digraphs, mat);

    cout << "\n\nCiphertext: " << cipher;

    string decrypted = playfair_decrypt(cipher, mat);

    cout << "\nDecrypted Text: " << decrypted;

    cout << "\nVerification: "
         << (verify(cipher, decrypted, mat) ? "SUCCESS" : "FAILED");

    return 0;
}