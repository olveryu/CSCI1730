
#comment

all: lab11



lab11: lab11.o
	g++ -Wall -g -o lab11 lab11.o

lab11.o: lab11.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors  -c lab11.cpp

clean:
	rm -f lab11.o
	rm -f lab11
