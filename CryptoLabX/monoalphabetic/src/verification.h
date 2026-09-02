#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <string>

using namespace std;

// Verify recovered plaintext by re-encrypting it
bool verify_solution(string plaintext,
                     string encryptionKey,
                     string originalCiphertext);

#endif

