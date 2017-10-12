FLAGS = -Wall -O0 -g -std=c++14 -pedantic-errors -lncurses

.PHONY: all clean

all: main

main: main.o textEditor.o
	g++ $(FLAGS) -o main main.o textEditor.o

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

textEditor.o: textEditor.cpp textEditor.h
	g++ $(FLAGS) -c textEditor.cpp

clean:
	rm -f main
	rm -f *.o