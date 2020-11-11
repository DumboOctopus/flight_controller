#include "uart.h"
#include <stdint.h>
#include <stdbool.h>


HalfDuplexUart::HalfDuplexUart(int togglePin, int rx, int tx): 
m_togglePin(togglePin), m_rx(rx), m_tx(tx) {


}

bool HalfDuplexUart::send(uint8_t* buffer, int length){
	return false;
}

uint8_t HalfDuplexUart::receive() {
	return 0;
}