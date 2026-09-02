#include <bits/stdc++.h>

using namespace std;

void freq_anal(string text){
    int freq[26]={0};
    for(char c:text){
        if(c>='A' and c<='Z') freq[c-'A']++;
    }

    cout<<"Frequence analysis"<<endl;

    for(int i=0;i<26;i++){
        if(freq[i]>0){
            cout<<char('A'+i)<<" : "<<freq[i]<<endl;
        }
    }
}