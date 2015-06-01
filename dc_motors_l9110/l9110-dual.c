#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

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

#define AIB_PIN 0
#define AIA_PIN 1
#define BIB_PIN 3
#define BIA_PIN 4
//#define SERVO_PIN 2

#define B_SCALE 0.9
#define A_SCALE 1.0

void backward(int speed) {
	softPwmWrite(AIA_PIN, 0);
	softPwmWrite(AIB_PIN, 0.8 * speed);
	softPwmWrite(BIA_PIN, 0);
	softPwmWrite(BIB_PIN, 1.0 * speed);
}

void forward(int speed) {
	softPwmWrite(AIA_PIN, A_SCALE * speed);
	softPwmWrite(AIB_PIN, 0);
	softPwmWrite(BIA_PIN, B_SCALE * speed);
	softPwmWrite(BIB_PIN, 0);
}

void left(int speed) {
	softPwmWrite(AIA_PIN, A_SCALE * speed);
	softPwmWrite(AIB_PIN, 0);
	softPwmWrite(BIA_PIN, 0);
	softPwmWrite(BIB_PIN, B_SCALE * speed);
}
 
void right(int speed) {
	softPwmWrite(AIA_PIN, 0);
	softPwmWrite(AIB_PIN, A_SCALE * speed);
	softPwmWrite(BIA_PIN, B_SCALE * speed);
	softPwmWrite(BIB_PIN, 0);
}

int main(void) {
	wiringPiSetup();
	if (0 != softPwmCreate (AIA_PIN, 0, 100))
		printf("Falied to create pwm pin AIA");
	if (0 != softPwmCreate (AIB_PIN, 0, 100))
		printf("Falied to create pwm pin AIB");
	if (0 != softPwmCreate (BIA_PIN, 0, 100))
		printf("Falied to create pwm pin BIA");
	if (0 != softPwmCreate (BIB_PIN, 0, 100))
		printf("Falied to create pwm pin BIB");
	
	int speed = 0;
	char dir = 'f';
	while (1) {	
		scanf("%c %d", &dir, &speed);
		if (dir == 'f') {
			forward(speed);
		} else if (dir == 'b') {
			backward(speed);
		} else if (dir == 'r') {
			right(speed);
		} else if (dir == 'l') {
			left(speed);
		}
		printf("Dir set %c, Speed set %d\n", dir, speed);
	}
	return 0;
}
