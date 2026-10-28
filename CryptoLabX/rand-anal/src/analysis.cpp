#include "analysis.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <cmath>
#include <iomanip>
#include <cstdint>
#include <algorithm>

using namespace std;

// Read binary data from a file.
vector<unsigned char> read_binary_file(const string& filename) {
    ifstream file(filename, ios::binary);

    if (!file) {
        throw runtime_error("Cannot open file: " + filename);
    }

    return vector<unsigned char>(
        istreambuf_iterator<char>(file),
        istreambuf_iterator<char>()
    );
}

// Count the number of 1 bits in a byte.
int count_ones(unsigned char byte) {
    int count = 0;

    for (int i = 0; i < 8; i++) {
        if ((byte >> i) & 1) {
            count++;
        }
    }

    return count;
}

// Calculate lag-1 Pearson correlation for byte values.
double calculate_correlation(
    const vector<unsigned char>& data
) {
    size_t n = data.size();

    if (n < 2) {
        return 0.0;
    }

    long double mean = 0;

    for (unsigned char byte : data) {
        mean += byte;
    }

    mean /= n;

    long double numerator = 0;
    long double denominator_x = 0;
    long double denominator_y = 0;

    for (size_t i = 0; i + 1 < n; i++) {
        long double x = data[i] - mean;
        long double y = data[i + 1] - mean;

        numerator += x * y;
        denominator_x += x * x;
        denominator_y += y * y;
    }

    if (denominator_x == 0 || denominator_y == 0) {
        return 0.0;
    }

    return static_cast<double>(
        numerator / sqrt(denominator_x * denominator_y)
    );
}

// Count repeated adjacent bytes.
size_t count_repeated_bytes(
    const vector<unsigned char>& data
) {
    size_t count = 0;

    for (size_t i = 1; i < data.size(); i++) {
        if (data[i] == data[i - 1]) {
            count++;
        }
    }

    return count;
}

// Count repeated adjacent 4-byte blocks.
// Example: ABCDABCD contains one repeated adjacent block.
size_t count_repeated_4byte_blocks(
    const vector<unsigned char>& data
) {
    size_t count = 0;

    for (size_t i = 0; i + 7 < data.size(); i++) {
        bool same = true;

        for (size_t j = 0; j < 4; j++) {
            if (data[i + j] != data[i + j + 4]) {
                same = false;
                break;
            }
        }

        if (same) {
            count++;
        }
    }

    return count;
}

// Calculate the byte-frequency chi-square statistic.
double calculate_chi_square(
    const array<uint64_t, 256>& frequency,
    size_t total_bytes
) {
    if (total_bytes == 0) {
        return 0.0;
    }

    double expected =
        static_cast<double>(total_bytes) / 256.0;

    double chi_square = 0.0;

    for (int i = 0; i < 256; i++) {
        double difference =
            static_cast<double>(frequency[i]) - expected;

        chi_square +=
            (difference * difference) / expected;
    }

    return chi_square;
}

// Main analysis function.
void analyze_file(
    const string& filename,
    const string& output_csv
) {
    vector<unsigned char> data = read_binary_file(filename);

    size_t n = data.size();

    if (n == 0) {
        throw runtime_error("Input file is empty: " + filename);
    }

    array<uint64_t, 256> frequency{};

    uint64_t total_ones = 0;

    // Count byte frequencies and 1 bits.
    for (unsigned char byte : data) {
        frequency[byte]++;
        total_ones += count_ones(byte);
    }

    size_t repeated_bytes =
        count_repeated_bytes(data);

    size_t repeated_blocks =
        count_repeated_4byte_blocks(data);

    double correlation =
        calculate_correlation(data);

    double chi_square =
        calculate_chi_square(frequency, n);

    uint64_t total_bits =
        static_cast<uint64_t>(n) * 8;

    double bit_one_fraction =
        static_cast<double>(total_ones) / total_bits;

    double repeated_byte_fraction =
        n > 1
        ? static_cast<double>(repeated_bytes) / (n - 1)
        : 0.0;

    // Write detailed results to CSV.
    ofstream csv(output_csv);

    if (!csv) {
        throw runtime_error(
            "Cannot create output file: " + output_csv
        );
    }

    csv << "Metric,Value\n";

    csv << "Input file," << filename << '\n';
    csv << "Total bytes," << n << '\n';
    csv << "Total bits," << total_bits << '\n';

    csv << fixed << setprecision(10);

    csv << "One-bit fraction,"
        << bit_one_fraction << '\n';

    csv << "Zero-bit fraction,"
        << (1.0 - bit_one_fraction) << '\n';

    csv << "Repeated adjacent bytes,"
        << repeated_bytes << '\n';

    csv << "Repeated adjacent byte fraction,"
        << repeated_byte_fraction << '\n';

    csv << "Repeated adjacent 4-byte blocks,"
        << repeated_blocks << '\n';

    csv << "Lag-1 byte correlation,"
        << correlation << '\n';

    csv << "Byte-frequency chi-square,"
        << chi_square << '\n';

    csv << "Chi-square degrees of freedom,255\n";

    csv << "\nByte,Frequency\n";

    for (int i = 0; i < 256; i++) {
        csv << i << ',' << frequency[i] << '\n';
    }

    csv.close();

    // Display a summary in the terminal.
    cout << "\n====================================\n";
    cout << "RANDOM DATA ANALYSIS\n";
    cout << "====================================\n";

    cout << "Input file: " << filename << '\n';
    cout << "Total bytes: " << n << '\n';

    cout << fixed << setprecision(6);

    cout << "One-bit fraction: "
         << bit_one_fraction << '\n';

    cout << "Zero-bit fraction: "
         << 1.0 - bit_one_fraction << '\n';

    cout << "Repeated adjacent bytes: "
         << repeated_bytes << '\n';

    cout << "Repeated adjacent 4-byte blocks: "
         << repeated_blocks << '\n';

    cout << "Lag-1 byte correlation: "
         << correlation << '\n';

    cout << "Byte-frequency chi-square: "
         << chi_square << '\n';

    cout << "Results saved to: "
         << output_csv << '\n';
}