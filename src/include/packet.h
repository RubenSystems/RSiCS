//
//packet.h
// RSiCSv2
//
//Created by Ruben Ticehurst - James on 29 / 04 / 2023.
//

#ifndef packet_h
#define packet_h

#include "config.h"
#define PACKET_DATA_SIZE MTU - sizeof(struct packet_header)

#ifdef __cplusplus
extern "C" {
#endif

enum packet_flags {
	PACKET_DATA,
	PACKET_FINAL,
	PACKET_PING,
};

struct packet_header {
	PACKET_INDEX_SIZE index;
	PACKET_ID_SIZE uid;
	enum packet_flags flags;
};

struct packet {
	struct {
		struct packet_header header;
		char data[PACKET_DATA_SIZE];
	} transmit;
	uint16_t data_size;
};

#ifdef __cplusplus
}
#endif

#endif /* packet_h */
