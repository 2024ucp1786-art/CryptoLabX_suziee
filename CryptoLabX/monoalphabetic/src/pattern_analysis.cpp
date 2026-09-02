#include <bits/stdc++.h>

using namespace std;

string gen_pat(string word){
    string pat="";
    char ns='A';
    char map[26];
    for(int i=0;i<26;i++){
        map[i]='0';
    }
    for(char c:word){
        int idx=c-'A';
        if(map[idx]=='0'){
            map[idx]=ns;
            ns++;
        }
        pat+=map[idx];
    }
    return pat;
}
void pat_anal(string text){
    cout<<"Pattern analysis"<<endl;
    string word="";
    for(int i=0;i<=text.size();i++){
        if(text[i]==' '||text[i]=='\n' || i==text.size()){
            if(word!=""){
                cout<<word<<" -> "<<gen_pat(word)<<endl;
                word="";
            }
        }
        else{
            word+=text[i];
        }
    }
}