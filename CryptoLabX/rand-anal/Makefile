CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = rand_analysis

SOURCES = src/main.cpp \
          src/linux_rng.cpp \
          src/openssl_rng.cpp \
          src/windows_rng.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
