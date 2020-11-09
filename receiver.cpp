
#include "receiver.h"
#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <stdio.h>          //memcpy
#include <string.h>



SRXL2Receiver::SRXL2Receiver(): uid(rand()), src_id(0x31), uart(1,2,3){
	
}

void SRXL2Receiver::performHandshake(int dest_id) {
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
		&buf + HEADER_LENGTH, 
		(const void *) &handshake, 
		sizeof(Handshake)
	);

	//this->computeCRC(buf, HANDSHAKE_PACKET_LEN-2, HANDSHAKE_PACKET_LEN);

	this->uart.send(buf, HANDSHAKE_PACKET_LEN);

}


SRXL2DataPacket* SRXL2Receiver::getPacket(){
	return NULL;
}

bool SRXL2Receiver::notBinded(){
	return false;
}