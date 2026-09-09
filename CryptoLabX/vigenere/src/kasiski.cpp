#include "../include/kasiski.h"

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


//finding repeated patterns
map<string, vector<int>>
find_repeated_patterns(const string& ciphertext, int length)
{
    map<string, vector<int>> patterns;

    for (int i = 0; i <= (int)ciphertext.size() - length; i++)
    {
        string pattern = ciphertext.substr(i, length);

        patterns[pattern].push_back(i);
    }

    // Remove patterns which occur only once
    for (auto it = patterns.begin(); it != patterns.end(); )
    {
        if (it->second.size() < 2)
            it = patterns.erase(it);
        else
            ++it;
    }

    return patterns;
}

//calculate distances
vector<int>
calculate_distances(
    const map<string, vector<int>>& patterns)
{
    vector<int> distances;

    for (const auto& entry : patterns)
    {
        const vector<int>& positions = entry.second;

        for (int i = 0; i < (int)positions.size(); i++)
        {
            for (int j = i + 1; j < (int)positions.size(); j++)
            {
                distances.push_back(
                    positions[j] - positions[i]
                );
            }
        }
    }

    return distances;
}


//finding factors
vector<int> find_factors(int number)
{
    vector<int> factors;

    for (int i = 2; i <= number; i++)
    {
        if (number % i == 0)
            factors.push_back(i);
    }

    return factors;
}


// kasiski analysis
int kasiski_analysis(const string& ciphertext)
{
    auto patterns =
        find_repeated_patterns(ciphertext, 3);

    auto distances =
        calculate_distances(patterns);

    map<int, int> factorCount;

    cout << "\nREPEATED PATTERNS\n";

    for (const auto& entry : patterns)
    {
        cout << entry.first << " : ";

        for (int position : entry.second)
            cout << position << " ";

        cout << "\n";
    }


    cout << "\nDISTANCES\n";

    for (int distance : distances)
    {
        cout << distance << " ";

        vector<int> factors =
            find_factors(distance);

        for (int factor : factors)
        {
            // Consider reasonable key lengths
            if (factor <= 20)
                factorCount[factor]++;
        }
    }

    cout << "\n";


    cout << "\nPOSSIBLE KEY LENGTHS\n";

    int bestLength = 1;
    int bestCount = 0;

    for (const auto& entry : factorCount)
    {
        cout << "Length "
             << entry.first
             << " -> "
             << entry.second
             << " occurrences\n";

        if (entry.second > bestCount)
        {
            bestCount = entry.second;
            bestLength = entry.first;
        }
    }

    return bestLength;
}