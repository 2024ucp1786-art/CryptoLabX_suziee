#ifndef CRYPTANALYSIS_H
#define CRYPTANALYSIS_H

#include <string>

using namespace std;

// Apply the current ciphertext -> plaintext substitutions
string apply_substitution(string ciphertext, string substitution);

// Display the current substitutions and partial plaintext
void display_partial_plaintext(string ciphertext, string substitution);

#endif

