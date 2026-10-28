#include "linux_rng.h"
#include "openssl_rng.h"
#include "windows_rng.h"
#include "analysis.h"  

#include <cstddef>
#include <filesystem>
#include <iostream>

int main() {
    constexpr std::size_t DATA_SIZE = 1024 * 1024;

    std::cout << "====================================\n";
    std::cout << " Cryptographic RNG Analysis\n";
    std::cout << " Data size: 1 MiB per source\n";
    std::cout << "====================================\n\n";

    // Create the output directory if necessary.
    std::error_code ec;
    std::filesystem::create_directories("data", ec);

    if (ec) {
        std::cerr << "Error creating data directory: "
                  << ec.message() << '\n';
        return 1;
    }

    bool linuxOK = generateLinuxRandom(
        "data/linux_urandom.bin", DATA_SIZE
    );

    bool opensslOK = generateOpenSSLRandom(
        "data/openssl_rand.bin", DATA_SIZE
    );

    // On Linux, this reports that Windows CNG must be run on Windows.
    bool windowsOK = generateWindowsRandom(
        "data/windows_cng.bin", DATA_SIZE
    );

    std::cout << "\n========== Generation Summary ==========\n";
    std::cout << "Linux /dev/urandom: "
              << (linuxOK ? "OK" : "FAILED") << '\n';
    std::cout << "OpenSSL rand: "
              << (opensslOK ? "OK" : "FAILED") << '\n';

#ifdef _WIN32
    std::cout << "Windows CNG: "
              << (windowsOK ? "OK" : "FAILED") << '\n';
#else
    std::cout << "Windows CNG: Run separately on Windows\n";
#endif

    if (!linuxOK || !opensslOK) {
        return 1;
    }

    std::cout << "\n========== Statistical Analysis ==========\n";

    analyze_file(
        "data/linux_urandom.bin",
        "results/linux_stats.csv"
    );

    analyze_file(
        "data/openssl_rand.bin",
        "results/openssl_stats.csv"
    );

#ifdef _WIN32
    if (windowsOK) {
        analyze_file(
            "data/windows_cng.bin",
            "results/windows_stats.csv"
        );
    }
#endif

    std::cout << "\nAnalysis complete. Check the results/ folder.\n";


    return 0;
}
