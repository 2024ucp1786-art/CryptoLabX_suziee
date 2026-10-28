#include "windows_rng.h"

#include <fstream>
#include <iostream>
#include <vector>

#ifdef _WIN32

#include <windows.h>
#include <bcrypt.h>

#pragma comment(lib, "bcrypt.lib")

bool generateWindowsRandom(const std::string& outputFile,
                           std::size_t size) {
    std::ofstream output(outputFile, std::ios::binary);

    if (!output) {
        std::cerr << "Error: Cannot create " << outputFile << '\n';
        return false;
    }

    // BCryptGenRandom accepts an ULONG buffer length.
    // Generate in chunks so the code also handles larger requests.
    const std::size_t chunkSize = 1024 * 1024;
    std::vector<unsigned char> buffer(
        size < chunkSize ? size : chunkSize
    );

    std::size_t remaining = size;

    while (remaining > 0) {
        ULONG amount = static_cast<ULONG>(
            remaining < buffer.size() ? remaining : buffer.size()
        );

        NTSTATUS status = BCryptGenRandom(
            nullptr,
            buffer.data(),
            amount,
            BCRYPT_USE_SYSTEM_PREFERRED_RNG
        );

        if (status < 0) {
            std::cerr << "Error: BCryptGenRandom failed. Status: "
                      << status << '\n';
            output.close();
            return false;
        }

        output.write(
            reinterpret_cast<const char*>(buffer.data()),
            static_cast<std::streamsize>(amount)
        );

        if (!output) {
            std::cerr << "Error: Failed to write output file\n";
            output.close();
            return false;
        }

        remaining -= amount;
    }

    output.close();

    if (!output) {
        std::cerr << "Error: Failed to finalize output file\n";
        return false;
    }

    std::cout << "Windows CNG: Generated " << size
              << " bytes in " << outputFile << '\n';

    return true;
}

#else

bool generateWindowsRandom(const std::string&, std::size_t) {
    std::cout
        << "Windows CNG skipped: run this component on Windows.\n";
    return true;
}

#endif
