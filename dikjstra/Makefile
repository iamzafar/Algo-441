###########################################################################
# Makefile for project
###########################################################################

all: driver.o Graph.o
	g++ -ansi -Wall driver.o Graph.o  -o driver


Graph.o: Graph.cpp
	g++ -ansi -Wall -c Graph.cpp

driver.o: driver.cpp
	g++ -ansi -Wall -c driver.cpp

run:
	./driver $(INPUT)
# -f removes any errors if the file is not present
clean:
	rm -rf *.o
	rm -f driver
	rm -f driver.out
	rm -f *~ *.h.gch *#[

