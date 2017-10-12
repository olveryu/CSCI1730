
#comment

all: lab10



lab10: lab10.o
	g++ -Wall -g -o lab10 lab10.o

lab10.o: lab10.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors  -c lab10.cpp

clean:
	rm -f lab10.o
	rm -f lab10
