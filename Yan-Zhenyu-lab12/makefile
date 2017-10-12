
#comment

all: lab12

lab12: lab12.o
	g++ -Wall -g -o lab12 lab12.o

lab12.o: lab12.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors  -c lab12.cpp

clean:
	rm -f lab12.o
	rm -f lab12
