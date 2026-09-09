#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <string>

// Re-encrypt the recovered plaintext and compare
// it with the original ciphertext.
bool verify(
    const std::string& originalCiphertext,
    const std::string& plaintext,
    const std::string& key
);

#endif

