all: l298-dual

l298-dual: l298-dual.o 
	g++ -o l298-dual -I/usr/local/include -L/usr/local/lib l298-dual.o -lwiringPi -lpthread
l298-dual.o: l298-dual.cpp
	g++ -I/usr/local/include -L/usr/local/lib -c l298-dual.cpp -lwiringPi -lpthread
clean:
	rm *.o l298-dual
