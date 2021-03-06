#include "l298-dual.h"

using namespace std;

void motors::backward(int speed) {
        softPwmWrite(PIN_A1, 0);
        softPwmWrite(PIN_A2, A_SCALE * speed);
        softPwmWrite(PIN_B1, 0);
        softPwmWrite(PIN_B2, B_SCALE * speed);
}

void motors::forward(int speed) {
        softPwmWrite(PIN_A1, speed);
        softPwmWrite(PIN_A2, 0);
        softPwmWrite(PIN_B1, speed);
        softPwmWrite(PIN_B2, 0);
}

void motors::left(int speed) {
        softPwmWrite(PIN_A1, speed);
        softPwmWrite(PIN_A2, 0);
        softPwmWrite(PIN_B1, 0);
        softPwmWrite(PIN_B2, speed);
}

void motors::right(int speed) {
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

void motors::stop () {
	softPwmWrite(PIN_A1, 0);
	softPwmWrite(PIN_A2, 0);
	softPwmWrite(PIN_B1, 0);
	softPwmWrite(PIN_B2, 0);
}

void motors::disableMotors() {
	motorAoff();
	motorBoff();
}

void motors::enableMotors() {
	motorAon();
	motorBon();
}

void motors::init()
{
	if (0 != softPwmCreate (PIN_A1, 0, 100))
                printf("Falied to create pwm pin AIA");
        if (0 != softPwmCreate (PIN_A2, 0, 100))
                printf("Falied to create pwm pin AIB");
        if (0 != softPwmCreate (PIN_B1, 0, 100))
                printf("Falied to create pwm pin BIA");
        if (0 != softPwmCreate (PIN_B2, 0, 100))
                printf("Falied to create pwm pin BIB");

        motors::enableMotors();
}

void motors::shutdown()
{
	motors::stop();
	motors::disableMotors();
}

/*int main(void) {

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
} */
