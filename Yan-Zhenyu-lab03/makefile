all: exclusive primesum armstrong bitsum endtime

exclusive: exclusive.o
	g++ -o exclusive exclusive.o

exclusive.o: exclusive.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c exclusive.cpp

primesum: primesum.o
	g++ -o primesum primesum.o

primesum.o: primesum.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c primesum.cpp

armstrong: armstrong.o
	g++ -o armstrong armstrong.o

armstrong.o: armstrong.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c armstrong.cpp

bitsum: bitsum.o
	g++ -o bitsum bitsum.o

bitsum.o: bitsum.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c bitsum.cpp

endtime: endtime.o
	g++ -o endtime endtime.o

endtime.o: endtime.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c endtime.cpp

clean:
	rm -f exclusive
	rm -f exclusive.o
	rm -f primesum
	rm -f primesum.o
	rm -f armstrong
	rm -f armstrong.o
	rm -f bitsum
	rm -f bitsum.o
	rm -f endtime
	rm -f endtime.o