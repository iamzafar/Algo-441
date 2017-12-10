# this is sample makefile
CXX = g++ -std=c++11
CXXFLAGS = -Wall -g


all: test.o
	$(CXX) $(CXXFLAGS) test.o -o test

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

run:
	./test

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

