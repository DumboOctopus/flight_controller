
#include "uart.h"
#include <iostream>

int main() {
	HalfDuplexUart u(4,;
	while(1) {
		std::cout << u.recieve() << std::endl;
	}

}
