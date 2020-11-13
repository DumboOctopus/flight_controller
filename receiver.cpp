
#include "receiver.h"
#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <iostream>
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <stdio.h>          //memcpy
#include <string.h>
#include <unistd.h>


// from hobby horizon
uint16_t Crc16(uint16_t crc, uint8_t data){
	crc = crc ^ ((uint16_t)data << 8);
	for(int i = 0; i < 8; ++i){
		if(crc & 0x8000)
			crc = (crc << 1) ^ 0x1021;
		else
			crc = crc << 1;
	}
	return crc;
}


SRXL2Receiver::SRXL2Receiver(): uid(rand()), src_id(0x30), uart(7, "/dev/ttyAMA0"){
	performHandshake();	
}

void SRXL2Receiver::performHandshake() {
	
	std::cout << "here" << std::endl;
	int dest_id = -1;

	while(dest_id == -1) {
		uint8_t value;
		int read = this->uart.receive(&value);

		if(read > 0 && value == SRXL_MANUFACTURE_ID) {
			uint8_t type = this->uart.blockingReceive();
			
			uint8_t length = this->uart.blockingReceive();
			uint8_t recBuf[MAX_PACKET_LENGTH];

			recBuf[0] = SRXL_MANUFACTURE_ID;
			recBuf[1] = type;
			recBuf[2] = length;
			for(int i = 3; i < length; i++)
				recBuf[i] = this->uart.blockingReceive();

			if(this->verifyPacket(recBuf, length)) {
				if(type == HANDSHAKE_PACKET) {
					Handshake inHandshake;
					memcpy(&inHandshake, recBuf+HEADER_LENGTH, HANDSHAKE_PACKET_LEN-HEADER_LENGTH);
					dest_id = inHandshake.src_id;
				
					
				} else {
					return; // no need to do handshake
				}
			}
		} else {
			sleep(1);
		}
	}

	std::cout << dest_id << std::endl;

	Handshake handshake;
	handshake.src_id = this->src_id;
	handshake.dest_id = dest_id;
	handshake.priority = 10;
	handshake.baud_rate = 0;
	handshake.info = 0; // no fancy stuff yet;
	handshake.uid = this->uid;

	uint8_t buf[HANDSHAKE_PACKET_LEN];
	buf[0] = SRXL_MANUFACTURE_ID;
	buf[1] = HANDSHAKE_PACKET;
	buf[2] = HANDSHAKE_PACKET_LEN;
	memcpy(
		buf + HEADER_LENGTH, 
		(const void *) &handshake, 
		sizeof(Handshake)
	);

	this->addCRC(buf, HANDSHAKE_PACKET_LEN);
	int sent = this->uart.send(buf, HANDSHAKE_PACKET_LEN);
	std::cout << "Sent n bytes:" << sent << std::endl;
	std::cout << "Verify own packet: " <<  verifyPacket(buf, HANDSHAKE_PACKET_LEN) << std::endl;
	for(int i = 0; i < HANDSHAKE_PACKET_LEN; ++i){
		std::cout << (int) buf[i] << " ";
	}
	std::cout << std::endl;

}

void SRXL2Receiver::addCRC(uint8_t* buf, int maxLength) {
	uint16_t computedCRC = 0;

	// last two bytes are for crc
	for(uint8_t i = 0; i < maxLength -2; ++i){
		computedCRC = Crc16(computedCRC, buf[i]);
	}

	// upper byte because big endian
	buf[maxLength-2] = (uint8_t) (computedCRC >> 8);
	buf[maxLength-1] = (uint8_t) (computedCRC & 0xff);

}


bool SRXL2Receiver::verifyPacket(uint8_t* buf, int length) {
	// we will assume last 2 bytes are crc
	uint16_t computedCRC = 0;
	for(uint8_t i = 0; i < length -2; ++i){
		computedCRC = Crc16(computedCRC, buf[i]);
	}
	uint16_t rxCRC = ((uint16_t)buf[length-2] << 8) | (buf[length-1]);

	return computedCRC == rxCRC;
}


SRXL2DataPacket* SRXL2Receiver::getPacket(){
	return NULL;
}

bool SRXL2Receiver::notBinded(){
	return false;
}
