#ifndef VIGENERE_H
#define VIGENERE_H

#include <string>
#include <vector>

// Determine the probable Vigenere key
// from the Caesar shifts of each group.
std::string find_key(
    const std::vector<std::string>& groups
);

// Encrypt plaintext using a Vigenere key.
std::string vigenere_encrypt(
    const std::string& plaintext,
    const std::string& key
);

// Decrypt ciphertext using a Vigenere key.
std::string vigenere_decrypt(
    const std::string& ciphertext,
    const std::string& key
);

#endif

