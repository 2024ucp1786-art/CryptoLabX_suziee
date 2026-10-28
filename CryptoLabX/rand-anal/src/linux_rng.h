#ifndef LINUX_RNG_H
#define LINUX_RNG_H

#include <cstddef>
#include <string>

bool generateLinuxRandom(const std::string& outputFile,
                         std::size_t size);

#endif
