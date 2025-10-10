
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -O2 -Wall -Wextra

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

all: hero

hero: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f hero *.o
