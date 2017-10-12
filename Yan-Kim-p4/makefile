FLAGS = -Wall -O0 -g -std=c++14 -pedantic-errors -lreadline

all: main

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

Shell.o: Shell.cpp Shell.h
	g++ $(FLAGS) -c Shell.cpp

main: main.o Shell.o
	g++ $(FLAGS) -o main main.o Shell.o

clean:
	rm -f main
	rm -f *.o
