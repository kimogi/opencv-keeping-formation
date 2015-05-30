all: camera

CFLAGS += -I/usr/local/include
LDFLAGS += -L/usr/local/lib
LIBS += -lwiringPi -lpthread

camera: camera.o
	g++ -ggdb `pkg-config opencv --cflags --libs` $(LDFLAGS) -o camera camera.o $(LIBS)
camera.o: camera.cpp
	g++ -ggdb `pkg-config opencv --cflags --libs` $(CFLAGS) camera.cpp -c $(LIBS)
clean:
	rm *.o camera
