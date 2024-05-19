CXX = g++
CXXFLAGS =   -std=c++11 -g -pthread

SRCS = simulator.cpp WriteOutput.c helper.c
OBJS = $(SRCS:.cpp=.o)
EXEC = simulator

all: $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(filter-out WriteOutput.c helper.c , $(wildcard *.o)) simulator
