all: l9110-dual

l9110-dual: l9110-dual.o 
	gcc -o l9110-dual -I/usr/local/include -L/usr/local/lib l9110-dual.o -lwiringPi -lpthread
l9110-dual.o: l9110-dual.c
	gcc -I/usr/local/include -L/usr/local/lib -c l9110-dual.c -lwiringPi -lpthread
clean:
	rm *.o l9110-dual
