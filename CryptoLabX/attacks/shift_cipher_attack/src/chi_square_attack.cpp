#include <bits/stdc++.h>
using namespace std;

double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702,
    2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507,
    1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974,
    0.074
};

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

double chiSquare(string text)
{
    int freq[26] = {0};
    int tot = 0;

    for (char c : text)
    {
        if (isalpha(c))
        {
            c = toupper(c);
            freq[c - 'A']++;
            tot++;
        }
    }

    double chi = 0.0;

    for (int i = 0; i < 26; i++)
    {
        double expected = tot * englishFreq[i] / 100.0;

        if (expected > 0)
        {
            chi += (freq[i] - expected) *
                   (freq[i] - expected) /
                   expected;
        }
    }

    return chi;
}

int chiSquareAttack(string cipher)
{
    int bestKey = 0;
    double bestScore = 1e18;

    for (int i = 0; i < 26; i++)
    {
        string plain = decrypt(cipher, i);

        double score = chiSquare(plain);

        cout << "Key " << i
             << " | Score: " << score
             << " | Text: " << plain << endl;

        if (score < bestScore)
        {
            bestScore = score;
            bestKey = i;
        }
    }

    return bestKey;
}

int main()
{
    ifstream file(
        "attacks/shift_cipher_attack/testcases/encrypted_text.txt"
    );

    if (!file)
    {
        cout << "Error: Could not open Chi-Square test file."
             << endl;
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

    cout << "\nChi-Square Analysis:" << endl;
    cout << "====================" << endl;

    int predictedKey = chiSquareAttack(ciphertext);

    cout << "\nPredicted Key: "
         << predictedKey << endl;

    cout << "\nDecrypted Text:" << endl;
    cout << decrypt(ciphertext, predictedKey) << endl;

    return 0;
}