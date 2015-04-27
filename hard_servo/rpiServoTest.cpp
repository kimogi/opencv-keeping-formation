#include "rpiServo.h"
#include <iostream>

int unsigned const delayUs = 2000000;

using namespace std;

int main(void){

    rpiServo servo;
// Increase angle by 18 deg every 'delayUs' microseconds from 90 to 180
    servo.setAngle(90); // set servo to centre
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(108);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(126);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(144);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(162);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(180);
    usleep(delayUs);
	cout << "1" << endl;
// Decrease angle by 18 deg every 'delayUs' microseconds from 180 to 90
    servo.setAngle(162);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(144);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(126);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(108);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(90);
    usleep(delayUs);
	cout << "1" << endl;
// Decrease angle by 18 deg every 'delayUs' microseconds from 90 to 0
    servo.setAngle(72);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(54);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(36);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(18);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(0);
    usleep(delayUs);
	cout << "1" << endl;
// Increase angle by 18 deg every 'delayUs' microseconds from 0 to 90
    servo.setAngle(18);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(36);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(54);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(72);
    usleep(delayUs);
	cout << "1" << endl;
    servo.setAngle(90);
    usleep(delayUs);
	cout << "1" << endl;
    return 0;
}
