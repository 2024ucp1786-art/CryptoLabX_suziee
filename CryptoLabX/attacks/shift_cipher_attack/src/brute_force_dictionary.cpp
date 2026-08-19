#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

string decrypt(string text, int key)
{
    for (char &c : text)
    {
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base - key + 26) % 26 + base;
        }
    }

    return text;
}

int main()
{
    ifstream file("attacks/shift_cipher_attack/testcases/encrypted_text.txt");

    if (!file)
    {
        cout << "Error: Could not open encrypted_text.txt" << endl;
        return 1;
    }

    string ciphertext;
    string line;

    while (getline(file, line))
    {
        ciphertext += line;
        ciphertext += "\n";
    }

    file.close();

    cout << "Encrypted Text:" << endl;
    cout << ciphertext << endl;

    cout << "Brute Force Results:" << endl;
    cout << "====================" << endl;

    for (int key = 0; key < 26; key++)
    {
        cout << "Key " << key << ": "
             << decrypt(ciphertext, key) << endl;
    }

    return 0;
}
