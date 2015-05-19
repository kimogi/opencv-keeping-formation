#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/*
wp         rp
0  GPIO_0  17 a1b
1  GPIO_1  18 a1a
2  GPIO_2  27 servo
3  GPIO_3  22 b1b
4  GPIO_4  23 b1a
5  GPIO_5  24
6  GPIO_6  25
7  GPIO_7  4
17 GPIO_8  28
18 GPIO_9  29
19 GPIO_10 30
20 GPIO_11 31
*/

#define ENA 0
#define PIN_A1 1
#define PIN_A2 2
#define PIN_B1 3
#define PIN_B2 4
#define ENB 5

#define LOW 0
#define HIGH 1
#define B_SCALE 1.0
#define A_SCALE 1.0

using namespace std;

void backward(int speed) {
        softPwmWrite(PIN_A1, 0);
        softPwmWrite(PIN_A2, A_SCALE * speed);
        softPwmWrite(PIN_B1, 0);
        softPwmWrite(PIN_B2, B_SCALE * speed);
}

void forward(int speed) {
        softPwmWrite(PIN_A1, speed);
        softPwmWrite(PIN_A2, 0);
        softPwmWrite(PIN_B1, speed);
        softPwmWrite(PIN_B2, 0);
}

void left(int speed) {
        softPwmWrite(PIN_A1, speed);
        softPwmWrite(PIN_A2, 0);
        softPwmWrite(PIN_B1, 0);
        softPwmWrite(PIN_B2, speed);
}

void right(int speed) {
        softPwmWrite(PIN_A1, 0);
        softPwmWrite(PIN_A2, speed);
        softPwmWrite(PIN_B1, speed);
        softPwmWrite(PIN_B2, 0);
}

void motorAon() {
	analogWrite(ENA, HIGH);
}

void motorBon() {
	analogWrite(ENB, HIGH);
}

void motorAoff() {
	analogWrite(ENA, LOW);
}

void motorBoff() {
	analogWrite(ENB, LOW);
}

void stop () {
	softPwmWrite(PIN_A1, 0);
	softPwmWrite(PIN_A2, 0);
	softPwmWrite(PIN_B1, 0);
	softPwmWrite(PIN_B2, 0);
}

void disableMotors() {
	motorAoff();
	motorBoff();
}

void enableMotors() {
	motorAon();
	motorBon();
}

int main(void) {

	wiringPiSetup();
        if (0 != softPwmCreate (PIN_A1, 0, 100))
                printf("Falied to create pwm pin AIA");
        if (0 != softPwmCreate (PIN_A2, 0, 100))
                printf("Falied to create pwm pin AIB");
        if (0 != softPwmCreate (PIN_B1, 0, 100))
                printf("Falied to create pwm pin BIA");
        if (0 != softPwmCreate (PIN_B2, 0, 100))
                printf("Falied to create pwm pin BIB");

	enableMotors();

	bool run = 1;
	while (run) 
	{
		char c;
		int speed = 100;
		scanf("%c", &c);
		switch(c) {
			case 'f':    // key up
				cout << "forward..." << endl;
        	                forward (speed);
    				break;
   			case 'b':    // key down
  				cout << "backward..." << endl;
        	                backward (speed);
				break;
			case 'r':    // key right
				cout << "right..." << endl;
   		  	  	right (speed);
				break;
    			case 'l':    // key left
        			cout << "left..." << endl;
        	                left (speed);
				break;
			case 's':
				cout << "stop..." << endl;
        	               	stop();
				break;
			case 'e':
				run = 0;
				break;
		}
	}
	disableMotors();
	return 0;
}
