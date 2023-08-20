

#pragma once 
#include <stdint.h>

#define MTU 1500

struct header {
	uint8_t pkt_number;
	uint8_t pkt_total; 
	uint8_t options; 
}

struct packet { 
	struct header head; 
	uint8_t data[MTU - sizeof(struct header)];
}