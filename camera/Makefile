all: camera

camera: camera.o
	g++ -ggdb `pkg-config opencv --cflags --libs` -o camera camera.o
camera.o: camera.cpp
	g++ -ggdb `pkg-config opencv --cflags --libs` camera.cpp -c
clean:
	rm *.o camera
