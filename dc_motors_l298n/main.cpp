#include "l298-dual.h"

using namespace motors;
using namespace std;

int main(void) {

	wiringPiSetup();
	pinMode(PIN_A1, OUTPUT);
	pinMode(PIN_A2, OUTPUT);
	pinMode(PIN_B1, OUTPUT);
	pinMode(PIN_B2, OUTPUT);	

	init();

	bool run = 1;
	while (run) 
	{
		char c;
		int speed = 0;
		scanf("%c %d", &c, &speed);
		switch(c) {
			case 'f':   
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
	return 0; 
}

