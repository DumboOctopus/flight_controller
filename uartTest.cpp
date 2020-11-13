
#include "uart.h"
#include <iostream>


int main() {
	HalfDuplexUart u(4, "/dev/ttyAMA0");
	while(1) {
		uint8_t buf;
		std::cout << u.receive(&buf) << buf << std::endl;
	}

}
