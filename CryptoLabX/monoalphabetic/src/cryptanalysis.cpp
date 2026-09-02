#include <iostream>
#include <string>

#include "cryptanalysis.h"

using namespace std;


// Apply current substitution guesses to ciphertext
string apply_substitution(string ciphertext, string substitution)
{
    string plaintext = "";

    for(char ch : ciphertext)
    {
        // Convert lowercase ciphertext to uppercase
        if(ch >= 'a' && ch <= 'z')
        {
            ch = ch - 'a' + 'A';
        }

        // If it is an alphabet character
        if(ch >= 'A' && ch <= 'Z')
        {
            int index = ch - 'A';

            // Check whether a substitution is known
            if(substitution[index] != '_')
            {
                plaintext += substitution[index];
            }
            else
            {
                // Unknown substitution
                plaintext += '_';
            }
        }
        else
        {
            // Keep spaces, numbers and punctuation unchanged
            plaintext += ch;
        }
    }

    return plaintext;
}


// Display current substitutions and partial plaintext
void display_partial_plaintext(string ciphertext, string substitution)
{
    cout << "\nCurrent Substitution:\n";

    for(int i = 0; i < 26; i++)
    {
        if(substitution[i] != '_')
        {
            cout << char('A' + i)
                 << " -> "
                 << substitution[i]
                 << endl;
        }
    }

    string partialPlaintext =
        apply_substitution(ciphertext, substitution);

    cout << "\nPartial Plaintext:\n";
    cout << partialPlaintext << endl;
}

