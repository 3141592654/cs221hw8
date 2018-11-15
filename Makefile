CXX=g++
CXXFLAGS=-g -Wall -Wextra -pedantic -std=c++17
OPTFLAGS=-O0
LDFLAGS=$(OPTFLAGS) $(CXXFLAGS)

all: test_cities tsp

test_cities: test_cities.cc cities.cc cities.hh cities.o
	$(CXX) $(LDFLAGS) -o test_cities cities.o test_cities.cc

cities.o: cities.cc cities.hh
	$(CXX) $(LDFLAGS) -c -o cities.o cities.cc

tsp: tsp.cc cities.cc cities.hh cities.o
	$(CXX) $(LDFLAGS) -o tsp cities.o tsp.cc

clean:
	rm -rf *.o cities
