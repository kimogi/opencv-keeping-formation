all: chassis_robot

chassis_robot: GPIOClass.o chassis_robot.o
	g++ -o chassis_robot GPIOClass.o chassis_robot.o
chassis_robot.o: chassis_robot.cpp
	g++ -c chassis_robot.cpp
GPIOClass.o: GPIOClass.h GPIOClass.cpp
	g++ -c GPIOClass.cpp
clean:
	rm *.o chassis_robot
