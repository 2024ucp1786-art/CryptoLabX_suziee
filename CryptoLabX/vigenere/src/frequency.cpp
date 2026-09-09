#include "../include/frequency.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;


// English letter frequencies
double englishFrequency[26] =
{
    0.082, 0.015, 0.028, 0.043, 0.127,
    0.022, 0.020, 0.061, 0.070, 0.0015,
    0.0077, 0.040, 0.024, 0.067, 0.075,
    0.019, 0.00095, 0.060, 0.063, 0.091,
    0.028, 0.0098, 0.024, 0.0015, 0.020,
    0.00074
};


//index of coincidence

double calculate_ic(const string& text)
{
    int n = text.size();

    if (n <= 1)
        return 0.0;

    int frequency[26] = {0};

    for (char c : text)
        frequency[c - 'A']++;

    int numerator = 0;

    for (int i = 0; i < 26; i++)
    {
        numerator +=
            frequency[i] * (frequency[i] - 1);
    }

    return (double)numerator /
           (n * (n - 1));
}


//split ciphertext into groups

vector<string>
split_into_groups(
    const string& ciphertext,
    int keyLength)
{
    vector<string> groups(keyLength);

    for (int i = 0; i < (int)ciphertext.size(); i++)
    {
        groups[i % keyLength] += ciphertext[i];
    }

    return groups;
}


//frequence analysis

vector<int>
frequency_analysis(const string& group)
{
    vector<int> frequency(26, 0);

    for (char c : group)
        frequency[c - 'A']++;

    return frequency;
}


//find caesar shift using chi sq test

int find_shift(const string& group)
{
    int n = group.size();

    if (n == 0)
        return 0;

    int bestShift = 0;
    double bestScore = 1e100;


    // Try all 26 possible shifts
    for (int shift = 0; shift < 26; shift++)
    {
        int observed[26] = {0};

        for (char c : group)
        {
            int value =
                (c - 'A' - shift + 26) % 26;

            observed[value]++;
        }


        double score = 0.0;

        for (int i = 0; i < 26; i++)
        {
            double expected =
                n * englishFrequency[i];

            if (expected > 0)
            {
                score +=
                    (observed[i] - expected) *
                    (observed[i] - expected) /
                    expected;
            }
        }


        if (score < bestScore)
        {
            bestScore = score;
            bestShift = shift;
        }
    }

    return bestShift;
}