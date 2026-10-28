#ifndef OPENSSL_RNG_H
#define OPENSSL_RNG_H

#include <cstddef>
#include <string>

bool generateOpenSSLRandom(const std::string& outputFile,
                           std::size_t size);

#endif
