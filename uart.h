#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stdint.h>
#include <iostream>

class HalfDuplexUart {
public:
	HalfDuplexUart(int togglePin, std::string uartDevName);
	int send(uint8_t* buffer, int length);
	int receive(uint8_t* buf);
	~HalfDuplexUart();
private:
	int m_togglePin;
	int m_uart_fd;

	uint8_t buffer[255];
	int readIndex;
	int writeIndex;
};

#endif