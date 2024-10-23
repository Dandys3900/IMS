# Author: Tomas Daniel
# Login:  xdanie14

CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra
SRCS :=$(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
EXE := ims-sim

$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXE)

clean:
	rm -f $(EXE)

.PHONY: all clean
