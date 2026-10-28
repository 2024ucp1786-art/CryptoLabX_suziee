#include "windows_rng.h"

#include <fstream>
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")
#endif

bool generateWindowsRandom(const std::string& filename,
                           std::size_t size) {
#ifndef _WIN32

    (void)filename;
    (void)size;

    std::cout << "Windows CNG skipped: run this component on Windows.\n";
    return false;

#else

    std::vector<unsigned char> buffer(size);

    NTSTATUS status = BCryptGenRandom(
        nullptr,
        buffer.data(),
        static_cast<ULONG>(buffer.size()),
        BCRYPT_USE_SYSTEM_PREFERRED_RNG
    );

    if (status < 0) {
        std::cerr << "BCryptGenRandom failed: "
                  << status << '\n';
        return false;
    }

    std::ofstream output(filename, std::ios::binary);

    if (!output) {
        std::cerr << "Cannot open output file: "
                  << filename << '\n';
        return false;
    }

    output.write(
        reinterpret_cast<const char*>(buffer.data()),
        static_cast<std::streamsize>(buffer.size())
    );

    if (!output) {
        std::cerr << "Failed writing random data.\n";
        return false;
    }

    std::cout << "Windows CNG: Generated "
              << size << " bytes in "
              << filename << '\n';

    return true;

#endif
}
