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

#define PIN_A1 1
#define PIN_A2 2
#define PIN_B1 4
#define PIN_B2 3

#define LOW 0
#define HIGH 1
#define SCALE_A 0.9
#define SCALE_B 1.0

namespace motors
{
	void backward(int speed);
	void forward(int speed);
	void left(int speed);
	void right(int speed);
	void stop();
	void init();
}
