#include <bits/stdc++.h>

using namespace std;

string encryptText(string plaintext, string key);

void freq_anal(string text);

void word_frequency_analysis(string text);

void pat_anal(string text);

string apply_substitution(string ciphertext, string substitution);

void display_partial_plaintext(string ciphertext, string substitution);

bool verify_solution(string plaintext,
                     string encryptionKey,
                     string originalCiphertext);

int main()
{

    string plaintext="";
    string key;

    ifstream input("input/input.txt");


    if(!input)
    {
        cout<<"Cannot open input file"<<endl;
        return 1;
    }


    string line;


    while(getline(input,line))
    {
        plaintext += line;
        plaintext += "\n";
    }


    input.close();


    ifstream keyFile("key/substitution.txt");


    if(!keyFile)
    {
        cout<<"Cannot open key file"<<endl;
        return 1;
    }


    getline(keyFile,key);


    keyFile.close();



    if(key.length()!=26)
    {
        cout<<"Key must contain exactly 26 letters"<<endl;
        return 1;
    }

    string ciphertext;


    ciphertext = encryptText(
                    plaintext,
                    key
                 );



    cout<<"\nCiphertext generated:\n";

    cout<<ciphertext<<endl;

    ofstream output("output/ciphertext.txt");


    output<<ciphertext;


    output.close();


    freq_anal(ciphertext);


    word_frequency_analysis(ciphertext);


    pat_anal(ciphertext);


    cout<<"\nAll analysis completed!"<<endl;

    string substitution = "";

    for(int i=0;i<26;i++)
    {
        substitution += '_';
    }


    display_partial_plaintext(
            ciphertext,
            substitution
    );

    string recoveredPlaintext = plaintext;

    string recoveredKey = key;


    verify_solution(
            recoveredPlaintext,
            recoveredKey,
            ciphertext
    );

    return 0;
}