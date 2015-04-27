#include "GPIOClass.h"

using namespace std;

#define LOW "0"
#define HIGH "1"

//Motor A
GPIOClass* enableA = new GPIOClass("17");
GPIOClass* pinA1 = new GPIOClass("18");
GPIOClass* pinA2 = new GPIOClass("27");

//Motor B
GPIOClass* enableB = new GPIOClass("22");
GPIOClass* pinB1 = new GPIOClass("23");
GPIOClass* pinB2 = new GPIOClass("24");

void motorAforward() {
	pinA1->setval_gpio(HIGH);
	pinA2->setval_gpio(LOW);
}

void motorBforward() {
	pinB1->setval_gpio(LOW);
	pinB2->setval_gpio(HIGH);
}

void motorAbackward() {
	pinA1->setval_gpio(LOW);
	pinA2->setval_gpio(HIGH);
}

void motorBbackward() {
	pinB1->setval_gpio(HIGH);
	pinB2->setval_gpio(LOW);
}

void motorAstop() {
	pinA1->setval_gpio(HIGH);
	pinA2->setval_gpio(HIGH);
}

void motorBstop() {
	pinB1->setval_gpio(HIGH);
	pinB2->setval_gpio(HIGH);
}

void motorAcoast() {
	pinA1->setval_gpio(LOW);
	pinA2->setval_gpio(LOW);
}

void motorBcoast() {
	pinB1->setval_gpio(LOW);
	pinB2->setval_gpio(LOW);
}

void motorAon() {
	enableA->setval_gpio(HIGH);
}

void motorBon() {
	enableB->setval_gpio(HIGH);
}

void motorAoff() {
	enableA->setval_gpio(LOW);
}

void motorBoff() {
	enableB->setval_gpio(LOW);
}

void forward (int duration) {
	motorAforward();
	motorBforward();
	usleep(duration);
}
	
void backward (int duration) {
	motorAbackward();
	motorBbackward();
	usleep(duration);
}

void left (int duration) {
	motorAbackward();
	motorBforward();
	usleep(duration);
}

void right (int duration) {
	motorAforward();
	motorBbackward();
	usleep(duration);
}

void coast (int duration) {
	motorAcoast();
	motorBcoast();
	usleep(duration);
}

void breakRobot (int duration) {
	motorAstop();
	motorBstop();
	usleep(duration);
}

void disableMotors() {
	motorAoff();
	motorBoff();
}

void enableMotors() {
	motorAon();
	motorBon();
}

int RUNNING = 10000;

int main(void) {

        enableA->export_gpio();
        pinA1->export_gpio();
        pinA2->export_gpio();

        enableB->export_gpio();
        pinB1->export_gpio();
        pinB2->export_gpio();

        enableA->setdir_gpio("out");
        pinA1->setdir_gpio("out");
        pinA2->setdir_gpio("out");

        enableB->setdir_gpio("out");
        pinB1->setdir_gpio("out");
        pinB2->setdir_gpio("out");

/*
	enableMotors();
	int start_time = time(NULL);
	while (1) {
		//Forward for 1,5s
		cout << "forward..." << endl;
		forward (1500);

		//turn right
		cout << "right..." << endl;
		right (500);

		//Forward for 1,5s
		cout << "forward..." << endl;
		forward (1500);
		
		//turn left
		cout << "left..." << endl;
		left (1000);

		//Forward for 1,5s
		cout << "forward..." << endl;
		forward (1500);

		if (time(NULL) - start_time >= RUNNING) {
			break;
		}
	} */
	//disable motors
	disableMotors();
}
