all: stat minmax number degree time

stat: stat.o
	g++ -o stat stat.o

stat.o: stat.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c stat.cpp

minmax: minmax.o
	g++ -o minmax minmax.o

minmax.o: minmax.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c minmax.cpp

number: number.o
	g++ -o number number.o

number.o: number.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c number.cpp

degree: degree.o
	g++ -o degree degree.o

degree.o: degree.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c degree.cpp

time: time.o
	g++ -o time time.o

time.o: time.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c time.cpp

clean:
	rm -f stat
	rm -f stat.o
	rm -f minmax
	rm -f minmax.o
	rm -f number
	rm -f number.o
	rm -f degree
	rm -f degree.o
	rm -f time
	rm -f time.o
