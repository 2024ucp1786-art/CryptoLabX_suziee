#include <bits/stdc++.h>
using namespace std;
int main(){
     string ciphertext = encrypt(plaintext, actualKey);

    cout << "Plaintext : " << plaintext << endl;
    cout << "Key       : " << actualKey << endl;
    cout << "Ciphertext: " << ciphertext << endl;

    cout << "\nBRUTE FORCE\n";

    shift_cipher(ciphertext);

    cout << "\nDICTIONARY ATTACK\n";

    loadDictionary("../dictionary/english_words.txt");

    int dictionaryKey = dictionaryAttack(ciphertext);

    cout << "Predicted Dictionary Key: "
         << dictionaryKey << endl;

    cout << "\nCHI-SQUARE ATTACK\n";

    int chiKey = chiSquareAttack(ciphertext);

    cout << "Predicted Chi-Square Key: "
         << chiKey << endl;

    return 0;
}
