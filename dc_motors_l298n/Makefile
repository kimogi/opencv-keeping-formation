all: main

main: l298-dual.o  main.o
	g++ -o main -I/usr/local/include -L/usr/local/lib l298-dual.o main.o -lwiringPi -lpthread
main.o: main.cpp
	g++ -I/usr/local/include -L/usr/local/lib -c main.cpp -lwiringPi -lpthread
l298-dual.o: l298-dual.cpp l298-dual.h
	g++ -I/usr/local/include -L/usr/local/lib -c l298-dual.cpp -lwiringPi -lpthread
clean:
	rm *.o main
