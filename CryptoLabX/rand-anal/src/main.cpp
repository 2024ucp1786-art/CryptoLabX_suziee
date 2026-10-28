#include <iostream>
#include <cstdlib>
#include <string>
#include <cstddef>

#include "linux_rng.h"
#include "openssl_rng.h"
#include "windows_rng.h"
#include "analysis.h"

int main()
{
    const std::size_t DATA_SIZE = 1024 * 1024; // 1 MB

    std::cout << "Cryptographic RNG Analysis\n";
    std::cout << "Data size: 1 MiB per source\n";
    std::cout << "====================================\n";

    // Create output directories on Linux
    if (std::system("mkdir -p data results") != 0)
    {
        std::cerr << "Error: Could not create output directories.\n";
        return 1;
    }

    // Generate random data
    bool linuxOK =
        generateLinuxRandom("data/linux_urandom.bin", DATA_SIZE);

    bool opensslOK =
        generateOpenSSLRandom("data/openssl_rand.bin", DATA_SIZE);

#ifdef _WIN32
    bool windowsOK =
        generateWindowsRandom("data/windows_cng.bin", DATA_SIZE);
#endif

#ifndef _WIN32
    std::cout << "\nWindows CNG skipped: run this component on Windows.\n";
#endif

    // Display generation results
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

    if (!linuxOK || !opensslOK)
    {
        std::cerr << "\nError: Random data generation failed.\n";
        return 1;
    }

    // Analyze generated files
    std::cout << "\n========== Statistical Analysis ==========\n";

    try
    {
        analyze_file(
            "data/linux_urandom.bin",
            "results/linux_stats.csv"
        );

        analyze_file(
            "data/openssl_rand.bin",
            "results/openssl_stats.csv"
        );

#ifdef _WIN32
        if (windowsOK)
        {
            analyze_file(
                "data/windows_cng.bin",
                "results/windows_stats.csv"
            );
        }
#endif
    }
    catch (const std::exception& e)
    {
        std::cerr << "Analysis error: " << e.what() << '\n';
        return 1;
    }

    std::cout << "\nAnalysis complete. Check the results/ folder.\n";

    return 0;
}
