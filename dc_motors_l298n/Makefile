all: main

main: l298n-dual.o  main.o
	g++ -o main -I/usr/local/include -L/usr/local/lib l298n-dual.o main.o -lwiringPi -lpthread
main.o: main.cpp
	g++ -I/usr/local/include -L/usr/local/lib -c main.cpp -lwiringPi -lpthread
l298n-dual.o: l298n-dual.cpp l298n-dual.h
	g++ -I/usr/local/include -L/usr/local/lib -c l298n-dual.cpp -lwiringPi -lpthread
clean:
	rm *.o main
