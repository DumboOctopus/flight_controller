#include "receiver.h"
//#include "flight.h"
#include <stdbool.h>
#include <unistd.h>
//#include <wiringPi.h>

bool bindButtonPressed();

int main(){
	//wiringPiSetup();	
	SRXL2Receiver receiver;

	while(receiver.notBinded()) {
		if(bindButtonPressed()) {
			//receiver.bind();
		}
		sleep(500); // allow the receiver thread to run
	}

	while(true) {
		SRXL2DataPacket* packet = receiver.getPacket();

	}
	return 0;
}


bool bindButtonPressed() {
	return true;
}