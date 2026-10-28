#include "linux_rng.h"

#include <fstream>
#include <iostream>
#include <vector>

#ifndef _WIN32

bool generateLinuxRandom(const std::string& outputFile,
                         std::size_t size) {
    std::ifstream randomSource("/dev/urandom", std::ios::binary);

    if (!randomSource) {
        std::cerr << "Error: Cannot open /dev/urandom\n";
        return false;
    }

    std::vector<char> buffer(size);

    randomSource.read(buffer.data(),
                      static_cast<std::streamsize>(size));

    if (randomSource.gcount() != static_cast<std::streamsize>(size)) {
        std::cerr << "Error: Could not read the requested bytes\n";
        return false;
    }

    randomSource.close();

    std::ofstream output(outputFile, std::ios::binary);

    if (!output) {
        std::cerr << "Error: Cannot create " << outputFile << '\n';
        return false;
    }

    output.write(buffer.data(),
                 static_cast<std::streamsize>(buffer.size()));

    if (!output) {
        std::cerr << "Error: Failed to write output file\n";
        return false;
    }

    output.close();

    std::cout << "Linux RNG: Generated " << size
              << " bytes in " << outputFile << '\n';

    return true;
}

#else

bool generateLinuxRandom(const std::string&, std::size_t) {
    std::cerr << "Linux /dev/urandom is unavailable on Windows\n";
    return false;
}

#endif
