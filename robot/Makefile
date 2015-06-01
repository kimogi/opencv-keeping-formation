all: robot

CFLAGS += -I/usr/local/include
LDFLAGS += -L/usr/local/lib
LIBS += -lwiringPi -lpthread

l298n-dual.o: ../dc_motors_l298n/l298n-dual.cpp ../dc_motors_l298n/l298n-dual.h
	g++  $(CFLAGS) -c ../dc_motors_l298n/l298n-dual.cpp $(LIBS)

robot: robot.o l298n-dual.o
	g++ -ggdb `pkg-config opencv --cflags --libs` $(LDFLAGS) -o robot robot.o l298n-dual.o $(LIBS)

robot.o: robot.cpp
	g++ -ggdb `pkg-config opencv --cflags --libs` $(CFLAGS) robot.cpp -c $(LIBS)

clean:
	rm *.o robot
