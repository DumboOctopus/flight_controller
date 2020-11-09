#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stdint.h>

class HalfDuplexUart {
public:
	HalfDuplexUart(int togglePin, int rx, int tx);
	bool send(uint8_t* buffer, int length);
	bool uartReceive(uint8_t* buffer);
private:
	int m_togglePin;
	int m_rx;
	int m_tx;
};

#endif