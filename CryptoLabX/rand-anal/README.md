# Cryptographic Random Number Generator Analysis

## Objective
Evaluate operating-system random-number generation mechanisms and
investigate their suitability for cryptographic applications.

## Random Data Sources
1. Linux /dev/urandom
2. OpenSSL rand utility
3. Windows CNG (BCryptGenRandom)

## Project Structure
- src/: C++ source and header files
- scripts/: Random data generation scripts
- analysis/: Statistical analysis notebook
- data/: Generated binary datasets
- results/: Analysis results and plots
- docs/: Research references

## Experimental Requirements
- Generate at least 1 MiB of random data per source.
- Analyze byte frequencies and bit distributions.
- Investigate repeated patterns and serial correlations.
- Apply statistical tests.
- Compare the underlying generation mechanisms.
- Explain why statistical tests alone cannot guarantee cryptographic security.

## Implementation Status
Project structure initialized. Implementation is in progress.
