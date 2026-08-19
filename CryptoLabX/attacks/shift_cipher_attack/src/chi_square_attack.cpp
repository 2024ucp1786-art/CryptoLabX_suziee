#include <bits/stdc++.h>
using namespace std;
double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702,
    2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507,
    1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974,
    0.074
};
double chiSquare(string text){
    int freq(26)={0};
    int tot=0;
    for(char c:text){
        if(isalpha(c)){
            c=toupper(c);
            freq[c-'A']++;
            tot++;
        }
    }
    double chi=0.0;
    for(int i=0;i<26;i++){
        double expected=tot*englishFreq[i]/100.0;
        if(expected>0){
            chi+=(freq[i]-expected)*(freq[i]-expected)/expected;
        }
    }
    return chi;
}
int chisquareTest(string cipher){
    int bestKey=0;
    double bestScore=DBL_MAX;
    for(int i=0;i<26;i++){
        string plain=decrypt(cipher,i);
        double score=chiSquare(plain);
        cout<<"Key "<<i
            <<"Score "<<score
            <<"Text "<<plain<<endl;
        if(score<bestScore){
            bestScore=score;
            bestKey=i;
        }
    }
    return bestKey;
}
