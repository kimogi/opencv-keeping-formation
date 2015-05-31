#include "l298-dual.h"

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

void init()
{
	if (0 != softPwmCreate (PIN_A1, 0, 100))
                printf("Falied to create pwm pin AIA");
        if (0 != softPwmCreate (PIN_A2, 0, 100))
                printf("Falied to create pwm pin AIB");
        if (0 != softPwmCreate (PIN_B1, 0, 100))
                printf("Falied to create pwm pin BIA");
        if (0 != softPwmCreate (PIN_B2, 0, 100))
                printf("Falied to create pwm pin BIB");

        enableMotors();
}

void shutdown()
{
	stop();
	disableMotors();
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
	return 0; */
}
