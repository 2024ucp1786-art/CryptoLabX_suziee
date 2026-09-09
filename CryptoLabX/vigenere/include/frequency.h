#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <string>
#include <vector>
#include <utility>

double calculate_ic(const std::string& text);

std::vector<int>
frequency_analysis(const std::string& group);

int find_shift(const std::string& group);

std::vector<std::string>
split_into_groups(
    const std::string& ciphertext,
    int keyLength
);

std::vector<std::pair<int, double>>
ic_key_length_analysis(
    const std::string& ciphertext,
    int maxKeyLength
);

#endif