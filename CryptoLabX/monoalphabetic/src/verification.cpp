#include <iostream>
#include <string>

#include "verification.h"
#include "encrypt.h"

using namespace std;


// Verify the recovered plaintext and key
bool verify_solution(string plaintext,
                     string encryptionKey,
                     string originalCiphertext)
{
    // Re-encrypt the recovered plaintext
    string generatedCiphertext =
        encryptText(plaintext, encryptionKey);

    // Compare with the original ciphertext
    if(generatedCiphertext == originalCiphertext)
    {
        cout << "\nSolution verified successfully!"
             << endl;

        cout << "The generated ciphertext matches "
             << "the original ciphertext." << endl;

        return true;
    }
    else
    {
        cout << "\nSolution verification failed!"
             << endl;

        cout << "The generated ciphertext does not "
             << "match the original ciphertext." << endl;

        return false;
    }
}

