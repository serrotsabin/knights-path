CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRCS = main.cpp

all: main

main:
	$(CXX) $(CXXFLAGS) $(SRCS) -o main

clean:
	rm -f main main.exe a.out a.exe