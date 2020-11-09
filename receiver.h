#ifndef RECIEVER_H
#define RECIEVER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "uart.h"

#define SRXL_MANUFACTURE_ID (0xA6)
#define HEADER_LENGTH (3) 
#define HANDSHAKE_PACKET (0x21)
#define HANDSHAKE_PACKET_LEN (14)

#define UART_TOGGLE_GPIO (11)

struct SRXL2DataPacket {
	uint8_t rssi;
	uint16_t frameLosses;
	uint32_t channelMask;
	uint16_t channelData[32];
};


// main class
class SRXL2Receiver {
public:
	SRXL2Receiver();
	SRXL2DataPacket* getPacket();
	bool notBinded();

private:
	const int uid;
	const int src_id;
	HalfDuplexUart uart;
	void performHandshake(int dest_id);

};




struct Handshake {
	uint8_t src_id;
	uint8_t dest_id;
	uint8_t priority;
	uint8_t baud_rate;
	uint8_t info;
	uint32_t uid;
} __attribute__((packed));






#endif