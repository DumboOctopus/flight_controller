#include "uart.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <iostream>
#ifndef DUMMY
#include <wiringPi.h>
#else
int OUTPUT,INPUT = 1;
void pinMode(int i, int x){}
void digitalWrite(int i, int x){}
#endif



HalfDuplexUart::HalfDuplexUart(int togglePin, std::string uartDev): 
m_togglePin(togglePin) {

	wiringPiSetup();
	pinMode(m_togglePin, OUTPUT);		// Configure GPIO0 as an output
	digitalWrite(m_togglePin, 1); // 1 is needed for reading
	
	m_uart_fd = open(uartDev.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
	if (m_uart_fd == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}
	
	//CONFIGURE THE UART
	//The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
	//	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
	//	CSIZE:- CS5, CS6, CS7, CS8
	//	CLOCAL - Ignore modem status lines
	//	CREAD - Enable receiver
	//	IGNPAR = Ignore characters with parity errors
	//	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
	//	PARENB - Parity enable
	//	PARODD - Odd parity (else even)
	struct termios options;
	tcgetattr(m_uart_fd, &options);
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(m_uart_fd, TCIFLUSH);
	tcsetattr(m_uart_fd, TCSANOW, &options);

}

int HalfDuplexUart::send(uint8_t* buffer, int length){
	digitalWrite(m_togglePin, 0); // 0 for writing
	int bytesWritten = write(m_uart_fd, buffer, length);
	digitalWrite(m_togglePin, 1); // 1 is needed for reading
	return bytesWritten;
}

int HalfDuplexUart::receive(uint8_t* buf) {
	int rx_length = read(m_uart_fd, (void*)buf, 1);		//Filestream, buffer to store in, number of bytes to read (max)
	return rx_length;
}

HalfDuplexUart::~HalfDuplexUart() {
	close(m_uart_fd);
}
