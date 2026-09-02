#include <bits/stdc++.h>

using namespace std;

string encryptText(string plaintext, string key);

void freq_anal(string text);

void word_frequency_analysis(string text);

void pat_anal(string text);

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



    return 0;
}