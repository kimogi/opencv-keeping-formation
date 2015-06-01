all: leader

leader: l298n-dual.o  leader.o
	g++ -o leader -I/usr/local/include -L/usr/local/lib l298n-dual.o leader.o -lwiringPi -lpthread
leader.o: leader.cpp
	g++ -I/usr/local/include -L/usr/local/lib -c leader.cpp -lwiringPi -lpthread
l298n-dual.o: ../dc_motors_l298n/l298n-dual.cpp ../dc_motors_l298n/l298n-dual.h
	g++ -I/usr/local/include -L/usr/local/lib -c ../dc_motors_l298n/l298n-dual.cpp -lwiringPi -lpthread
clean:
	rm *.o leader
