CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra
SRCS := $(wildcard *.cpp) $(wildcard entities/*.cpp)
OBJS := $(SRCS:.cpp=.o)
EXE := ims-sim

$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -lsimlib -o $(EXE)

clean:
	rm -f $(EXE)

run: ims-sim
	./ims-sim sim_config.json sim_config_copy.json

.PHONY: all run clean
