
#include "uart.h"
#include <iostream>


int main() {
	HalfDuplexUart u(7, "/dev/ttyAMA0");
	while(1) {
		uint8_t buf;
		int read  = u.receive(&buf);
		if(read > 0) {
			if(buf == 0xa6) {
				std::cout << "Found start" << std::endl;
			}
		}
	}

}
