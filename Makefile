# Makefile for project 2 milestone 1
# compiling it with c++ 11
CXX = g++ -std=c++0x
CXXFLAGS = -ansi -Wall -g


all: lcs_length.o
	$(CXX) $(CXXFLAGS) lcs_length.o -o lcs_length

lcs_length.o: lcs_length.cpp
	$(CXX) $(CXXFLAGS) -c lcs_length.cpp

run:
	./lcs_length

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

