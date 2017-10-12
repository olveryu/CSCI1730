
#comment

all: lab08

lab08: lab08.o
	g++ -Wall -g -o lab08 lab08.o

lab08.o: lab08.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors  -c lab08.cpp

clean:
	rm -f lab08.o
	rm -f lab08
