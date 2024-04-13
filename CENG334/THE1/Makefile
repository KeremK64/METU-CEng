
CXX = g++
CXXFLAGS =   -std=c++11 -g

SRCS = eshell.cpp parser.c
OBJS = $(SRCS:.cpp=.o)
EXEC = eshell

all: $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(filter-out parser.c, $(wildcard *.o)) eshell
