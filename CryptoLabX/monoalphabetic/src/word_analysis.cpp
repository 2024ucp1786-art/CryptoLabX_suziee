#include<bits/stdc++.h>

using namespace std;

void word_frequency_analysis(string text)
{

    string words[1000];
    int count[1000];

    int totalWords = 0;

    for(int i=0;i<1000;i++)
    {
        count[i]=0;
    }



    string current="";

    for(int i=0;i<=text.length();i++)
    {

        if(text[i]==' ' || text[i]=='\n' || i==text.length())
        {

            if(current!="")
            {

                bool found=false;


                for(int j=0;j<totalWords;j++)
                {

                    if(words[j]==current)
                    {
                        count[j]++;
                        found=true;
                        break;
                    }

                }



                if(!found)
                {
                    words[totalWords]=current;
                    count[totalWords]=1;
                    totalWords++;
                }


                current="";
            }

        }

        else
        {
            current+=text[i];
        }

    }




    cout<<"\nWord Frequency Analysis\n";


    for(int i=0;i<totalWords;i++)
    {

        cout<<words[i]<<" : "<<count[i]<<endl;

    }

}