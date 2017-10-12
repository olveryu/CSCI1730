FLAGS = -Wall -O0 -g -std=c++14 -pedantic-errors

.phony: all clean

all: main

main: main.o GradeBook.o
	g++  $(FLAGS) -o  main main.o GradeBook.o

main.o: main.cpp
	g++  $(FLAGS) -c main.cpp

Gradebook.o: GradeBook.cpp gradebook.h
	g++  $(FLAGS) -c Gradebook.cpp

clean:
	rm -f main
	rm -f *.o