#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>
#include "softServo.h"

int main (int argc, char **argv) {
	if (wiringPiSetup () == -1) {
		fprintf (stdout, "oops: %s\n", strerror (errno)) ;
		return 1 ;
	}

	softServoSetup (0, 1, 2, 3, 4, 5, 6, 7) ;
	
	while (1) {
		int value;
		scanf("%d", &value);
	
		softServoWrite (0, value) ;
		delay (10);
	}
}
