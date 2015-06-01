#include "../dc_motors_l298n/l298n-dual.h"

#define FLASH_PIN 7

using namespace std;

int main(void) {

	wiringPiSetup();
	pinMode(PIN_A1, OUTPUT);
	pinMode(PIN_A2, OUTPUT);
	pinMode(PIN_B1, OUTPUT);
	pinMode(PIN_B2, OUTPUT);	
	pinMode(FLASH_PIN, OUTPUT);

	motors::init();
	digitalWrite(FLASH_PIN, HIGH);
	
	bool run = 1;
	while (run) 
	{
		char c;
		int speed = 0;
		scanf("%c %d", &c, &speed);
		switch(c) {
			case 'f':   
				cout << "forward..." << endl;
				//digitalWrite(FLASH_PIN, HIGH);
        	                motors::forward (speed);
    				break;
   			case 'b':    // key down
  				cout << "backward..." << endl;
				//digitalWrite(FLASH_PIN, HIGH);
        	                motors::backward (speed);
				break;
			case 'r':    // key right
				cout << "right..." << endl;
				//digitalWrite(FLASH_PIN, HIGH);
   		  	  	motors::right (speed);
				break;
    			case 'l':    // key left
        			cout << "left..." << endl;
				//digitalWrite(FLASH_PIN, HIGH);
        	                motors::left (speed);
				break;
			case 's':
				cout << "stop..." << endl;
				//digitalWrite(FLASH_PIN, LOW);
        	               	motors::stop();
				break;
			case 'e':
				run = 0;
				break;
		}
	}
	digitalWrite(FLASH_PIN, LOW);
	return 0; 
}

