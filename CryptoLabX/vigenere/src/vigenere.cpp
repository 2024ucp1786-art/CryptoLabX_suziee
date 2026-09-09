#include "../include/vigenere.h"
#include "../include/frequency.h"

using namespace std;

// --------------------------------------------------
// Find Vigenere Key
// --------------------------------------------------
// Each ciphertext group corresponds to one character
// of the Vigenere key.
//
// find_shift() from frequency.cpp determines the
// Caesar shift for each group.
//
// Shift 0 -> A
// Shift 1 -> B
// Shift 2 -> C
// ...
// Shift 25 -> Z
// --------------------------------------------------

string find_key(
    const vector<string>& groups)
{
    string key;

    for (const string& group : groups)
    {
        int shift = find_shift(group);

        key += char('A' + shift);
    }

    return key;
}


// --------------------------------------------------
// Vigenere Decryption
// --------------------------------------------------
// Formula:
//
// Plaintext = (Ciphertext - Key) mod 26
//
// Example:
// Cipher = D (3)
// Key    = B (1)
//
// Plain = (3 - 1) mod 26
//       = C (2)
// --------------------------------------------------

string vigenere_decrypt(
    const string& ciphertext,
    const string& key)
{
    string plaintext;

    // Prevent division by zero if key is empty.
    if (key.empty())
    {
        return plaintext;
    }

    for (int i = 0;
         i < static_cast<int>(ciphertext.size());
         i++)
    {
        int cipherValue =
            ciphertext[i] - 'A';

        int keyValue =
            key[i % key.size()] - 'A';

        int plainValue =
            (cipherValue - keyValue + 26) % 26;

        plaintext +=
            char('A' + plainValue);
    }

    return plaintext;
}


// --------------------------------------------------
// Vigenere Encryption
// --------------------------------------------------
// Formula:
//
// Ciphertext = (Plaintext + Key) mod 26
//
// Example:
// Plain = C (2)
// Key   = B (1)
//
// Cipher = (2 + 1) mod 26
//        = D (3)
// --------------------------------------------------

string vigenere_encrypt(
    const string& plaintext,
    const string& key)
{
    string ciphertext;

    // Prevent division by zero if key is empty.
    if (key.empty())
    {
        return ciphertext;
    }

    for (int i = 0;
         i < static_cast<int>(plaintext.size());
         i++)
    {
        int plainValue =
            plaintext[i] - 'A';

        int keyValue =
            key[i % key.size()] - 'A';

        int cipherValue =
            (plainValue + keyValue) % 26;

        ciphertext +=
            char('A' + cipherValue);
    }

    return ciphertext;
}

