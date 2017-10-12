FLAGS = -Wall -O0 -g -std=c++14 -pedantic-errors

.PHONY: all clean

all: cal date env false head tail ln ls pwd true wc mkdir

cal: cal.o
	g++ $(FLAGS) -o cal cal.o

cal.o: cal.cpp
	g++ $(FLAGS) -c cal.cpp

date: date.o
	g++ $(FLAGS) -o date date.o

date.o: date.cpp
	g++ $(FLAGS) -c date.cpp

env: env.o
	g++ $(FLAGS) -o env env.o

env.o: env.cpp
	g++ $(FLAGS) -c env.cpp

false: false.o
	g++ $(FLAGS) -o false false.o

false.o: false.cpp
	g++ $(FLAGS) -c false.cpp

head: head.o
	g++ $(FLAGS) -o head head.o

head.o: head.cpp
	g++ $(FLAGS) -c head.cpp

tail: tail.o
	g++ $(FLAGS) -o tail tail.o

tail.o: tail.cpp
	g++ $(FLAGS) -c tail.cpp

ln: ln.o
	g++ $(FLAGS) -o ln ln.o

ln.o: ln.cpp
	g++ $(FLAGS) -c ln.cpp

ls: ls.o
	g++ $(FLAGS) -o ls ls.o

ls.o: ls.cpp
	g++ $(FLAGS) -c ls.cpp

pwd: pwd.o
	g++ $(FLAGS) -o pwd pwd.o

pwd.o: pwd.cpp
	g++ $(FLAGS) -c pwd.cpp

true: true.o
	g++ $(FLAGS) -o true true.o

true.o: true.cpp
	g++ $(FLAGS) -c true.cpp

wc: wc.o
	g++ $(FLAGS) -o wc wc.o

wc.o: wc.cpp
	g++ $(FLAGS) -c wc.cpp

mkdir: mkdir.o
	g++ $(FLAGS) -o mkdir mkdir.o

mkdir.o: mkdir.cpp
	g++ $(FLAGS) -c mkdir.cpp


clean:
	rm -f *.o
	rm -f cal
	rm -f date
	rm -f env
	rm -f false
	rm -f head
	rm -f tail
	rm -f ln
	rm -f ls
	rm -f pwd
	rm -f true
	rm -f wc
	rm -f mkdir
