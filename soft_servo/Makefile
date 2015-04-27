all: servo

servo: servo.o softServo.o
	gcc -o servo -I/usr/local/include -L/usr/local/lib servo.o softServo.o -lwiringPi
servo.o: servo.c
	gcc -I/usr/local/include -L/usr/local/lib -c servo.c -lwiringPi
softservo.o: softServo.c softServo.c
	gcc -I/usr/local/include -L/usr/local/lib -c softServo.c -lwiringPi
clean:
	rm *.o servo
