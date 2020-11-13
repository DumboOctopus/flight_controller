#include "receiver.h"
//#include "flight.h"
#include <stdbool.h>
#include <unistd.h>
#include <iostream>
//#include <wiringPi.h>

bool bindButtonPressed();

int main(){
	//wiringPiSetup();	
	std::cout << "Starting..." << std::endl;
	SRXL2Receiver receiver;
	std::cout << "Performed handshake" << std::endl;

	while(receiver.notBinded()) {
		if(bindButtonPressed()) {
			//receiver.bind();
		}
	}

	while(true) {
		SRXL2DataPacket* packet = receiver.getPacket();

	}
	return 0;
}


bool bindButtonPressed() {
	return true;
}
