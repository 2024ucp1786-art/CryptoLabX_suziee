#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

string encrypt(string text, int key) {
    for (char &c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + key) % 26 + base;
        }
    }

    return text;
}

int main() {
    ifstream file("../dictionary/english_words.txt");

    if (!file) {
        cout << "Error: Could not open english_words.txt" << endl;
        return 1;
    }

    string text;
    getline(file, text);

    int key = 3;

    cout << "Original  : " << text << endl;
    cout << "Key       : " << key << endl;
    cout << "Encrypted : " << encrypt(text, key) << endl;

    file.close();

    return 0;
}
