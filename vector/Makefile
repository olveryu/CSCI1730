FLAGS = -Wall -O0 -g -std=c++14 -pedantic-errors

.PHONY: all clean doc

all: main

main: main.o Vector.o
	g++ $(FLAGS) -o main main.o Vector.o

main.o: main.cpp Vector.h
	g++ $(FLAGS) -c main.cpp

Vector.o: Vector.cpp Vector.h
	g++ $(FLAGS) -c Vector.cpp

doc:
	doxygen

clean:
	rm -f main
	rm -f *.o
	rm -rf doc
