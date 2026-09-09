#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "include/preprocessing.h"
#include "include/kasiski.h"
#include "include/frequency.h"
#include "include/vigenere.h"
#include "include/verification.h"

using namespace std;

int main()
{
    // --------------------------------------------------
    // Read ciphertext from file
    // --------------------------------------------------

    ifstream file("data/ciphertext.txt");

    if (!file)
    {
        cout << "Error: Unable to open ciphertext file.\n";
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();

    string ciphertext = buffer.str();

    file.close();

    // --------------------------------------------------
    // Step 1: Preprocess ciphertext
    // --------------------------------------------------

    ciphertext = clean_ciphertext(ciphertext);

    cout << "============================================\n";
    cout << "       VIGENERE CIPHER CRYPTANALYSIS\n";
    cout << "============================================\n";

    cout << "\nCleaned Ciphertext:\n";
    cout << ciphertext << "\n";

    cout << "\nCiphertext Length: "
         << ciphertext.length()
         << "\n";


    // --------------------------------------------------
    // Step 2: Kasiski Examination
    // --------------------------------------------------

    cout << "\n============================================\n";
    cout << "             KASISKI ANALYSIS\n";
    cout << "============================================\n";

    int keyLength = kasiski_analysis(ciphertext);

    cout << "\nEstimated Key Length: "
         << keyLength
         << "\n";


    // --------------------------------------------------
    // Step 3: Split ciphertext into groups
    // --------------------------------------------------

    cout << "\n============================================\n";
    cout << "             CIPHERTEXT GROUPS\n";
    cout << "============================================\n";

    vector<string> groups =
        split_into_groups(ciphertext, keyLength);

    for (int i = 0;
         i < static_cast<int>(groups.size());
         i++)
    {
        cout << "Group "
             << i + 1
             << ": "
             << groups[i]
             << "\n";
    }


    // --------------------------------------------------
    // Step 4: Frequency Analysis
    // --------------------------------------------------

    cout << "\n============================================\n";
    cout << "             FREQUENCY ANALYSIS\n";
    cout << "============================================\n";

    for (int i = 0;
         i < static_cast<int>(groups.size());
         i++)
    {
        cout << "\n--------------------------------------------\n";
        cout << "Group " << i + 1 << "\n";
        cout << "--------------------------------------------\n";

        vector<int> frequency =
            frequency_analysis(groups[i]);

        cout << "Letter\tFrequency\n";

        for (int j = 0; j < 26; j++)
        {
            cout << char('A' + j)
                 << "\t"
                 << frequency[j]
                 << "\n";
        }

        double ic =
            calculate_ic(groups[i]);

        cout << "Index of Coincidence (IC): "
             << ic
             << "\n";
    }


    // --------------------------------------------------
    // Step 5: Determine probable key
    // --------------------------------------------------

    cout << "\n============================================\n";
    cout << "             KEY RECOVERY\n";
    cout << "============================================\n";

    string key = find_key(groups);

    cout << "\nRecovered Key: "
         << key
         << "\n";


    // --------------------------------------------------
    // Step 6: Decrypt ciphertext
    // --------------------------------------------------

    cout << "\n============================================\n";
    cout << "             DECRYPTION\n";
    cout << "============================================\n";

    string plaintext =
        vigenere_decrypt(ciphertext, key);

    cout << "\nRecovered Plaintext:\n";
    cout << plaintext
         << "\n";


    // --------------------------------------------------
    // Step 7: Re-encrypt plaintext
    // --------------------------------------------------

    cout << "\n============================================\n";
    cout << "             VERIFICATION\n";
    cout << "============================================\n";

    string regeneratedCiphertext =
        vigenere_encrypt(plaintext, key);

    cout << "\nRe-encrypted Ciphertext:\n";
    cout << regeneratedCiphertext
         << "\n";


    // --------------------------------------------------
    // Step 8: Verify
    // --------------------------------------------------

    bool result =
        verify(
            ciphertext,
            plaintext,
            key
        );

    cout << "\nVerification Result: ";

    if (result)
    {
        cout << "SUCCESS\n";
        cout << "Re-encryption matches the original ciphertext.\n";
    }
    else
    {
        cout << "FAILED\n";
        cout << "Re-encryption does not match the original ciphertext.\n";
    }


    // --------------------------------------------------
    // Final Summary
    // --------------------------------------------------

    cout << "\n============================================\n";
    cout << "                 SUMMARY\n";
    cout << "============================================\n";

    cout << "Estimated Key Length : "
         << keyLength
         << "\n";

    cout << "Recovered Key        : "
         << key
         << "\n";

    cout << "Verification         : "
         << (result ? "PASSED" : "FAILED")
         << "\n";

    cout << "============================================\n";

    return 0;
}

