CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -pipe -Wall -Wextra -Wno-unused-result

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f code

.PHONY: all clean
