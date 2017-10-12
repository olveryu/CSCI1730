
#comment

all: lab09



lab09: lab09.o
	g++ -Wall -g -o lab09 lab09.o

lab09.o: lab09.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors  -c lab09.cpp

clean:
	rm -f lab09.o
	rm -f lab09
