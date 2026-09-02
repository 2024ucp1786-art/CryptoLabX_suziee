#include <bits/stdc++.h>

using namespace std;

string encryptText(string plain,string key){
    string cipher="";
    for(char c:plain){
        if(c>='a' and c<='z') c=c-'a'+'A';
        if(c>='A' and c<='Z') cipher+=key[c-'A'];
        else{
            if(c==' ') cipher+=c;
        }
    }
    return cipher;
}