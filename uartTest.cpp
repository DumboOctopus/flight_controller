
#include "uart.h"
#include <iostream>
#include <iomanip>


int main() {
	HalfDuplexUart u(7, "/dev/ttyAMA0");
	while(1) {
		uint8_t buf;
		int read  = u.receive(&buf);
		if(read > 0) {
			if(buf == 0xa6) {
				std::cout << "Found start" << std::endl;
				int type =  u.blockingReceive();
				std::cout << std::hex << type << std::dec << std::endl;
				u.blockingReceive();
				int src_id = u.blockingReceive();

				std::cout << std::hex << src_id << std::dec << std::endl;
				uint8_t x[14] = {
					166,
					33,
					14,
					48,
					16,
					10,
					0,
					4,
					49,
					50,
					51,
					52,
					224,
					143
				};

				//u.send(x, 14);


			}
		}
	}

}
