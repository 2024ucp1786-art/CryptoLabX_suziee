#include "../include/verification.h"
#include "../include/vigenere.h"

using namespace std;

// --------------------------------------------------
// Verification
// --------------------------------------------------
// The recovered plaintext is encrypted again using
// the recovered key.
//
// If the newly generated ciphertext is exactly equal
// to the original ciphertext, the cryptanalysis result
// is considered verified.
// --------------------------------------------------

bool verify(
    const string& originalCiphertext,
    const string& plaintext,
    const string& key)
{
    // Re-encrypt the recovered plaintext.
    string regeneratedCiphertext =
        vigenere_encrypt(plaintext, key);

    // Compare with the original ciphertext.
    return regeneratedCiphertext ==
           originalCiphertext;
}

