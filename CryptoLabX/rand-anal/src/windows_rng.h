#ifndef WINDOWS_RNG_H
#define WINDOWS_RNG_H

#include <cstddef>
#include <string>

bool generateWindowsRandom(const std::string& filename,
                           std::size_t size);

#endif
