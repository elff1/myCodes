CXX=g++
CXXFLAGES=-g -std=c++11 -Wall -pedantic

SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)
BIN=$(SRC:%.cc=%.out)

all: $(BIN)

%.out: %.o
	$(CXX) -o $@ $<

%.o: %.cc
	$(CXX) -o $@ -c $(CXXFLAGES) $<

clean:
	rm -f *.o
	rm -f *.out

