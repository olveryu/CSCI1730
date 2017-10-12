all: lab05 test

lab05: lab05.o
	g++ -Wall -g -lncurses -o lab05 lab05.o

test: test.o
	 g++ -Wall -g -lncurses -o test test.o

lab05.o: lab05.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -lpanel -lncurses -c lab05.cpp

test.o: test.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -lpanel -lncurses -c test.cpp
clean:
	rm -f lab05
	rm -f lab05.o
	rm -f test
	rm -f test.o
