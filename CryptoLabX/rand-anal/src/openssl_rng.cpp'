#include "openssl_rng.h"

#include <cstdlib>
#include <iostream>
#include <string>

bool generateOpenSSLRandom(const std::string& outputFile,
                           std::size_t size) {
    // The output path is quoted to support ordinary paths
    // containing spaces. Keep this argument under our control.
    std::string command =
        "openssl rand -out \"" + outputFile + "\" " +
        std::to_string(size);

    std::cout << "Generating random data using OpenSSL...\n";

    int status = std::system(command.c_str());

    if (status != 0) {
        std::cerr << "Error: OpenSSL command failed\n";
        return false;
    }

    std::cout << "OpenSSL RNG: Generated " << size
              << " bytes in " << outputFile << '\n';

    return true;
}
