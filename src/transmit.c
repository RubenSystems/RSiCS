//
//  transmit.c
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 01/05/2023.
//

#include "include/transmit.h"
#include <string.h>
#include <stdbool.h>
#include <math.h>


static PACKET_ID_SIZE __get_next_uid() {
	static uint8_t uid = 0;

	uid = (uid + 1) % MAX_PACKET_ID;
	return uid; 
}

enum transmit_response rsics_ping(struct connection * to_computer,
				  const char * session_token) {
	
	
	
	static struct packet_header header = {
		.index = 0, .flags = PACKET_FINAL | PACKET_PING
	};
	header.uid = __get_next_uid(); 

	struct packet pack = { .transmit = { .header = header },
			       .data_size = strnlen(session_token,
						    PACKET_DATA_SIZE - 1) };
	strncpy(pack.transmit.data, session_token, PACKET_DATA_SIZE - 1);
	return rsics_transmit_packet(&pack, to_computer);
}

enum transmit_response rsics_transmit(void * data, uint64_t length,
				      struct connection * computer) {
	struct packet pack;
	bool success = 1;
	uint32_t index = 0;
	pack.transmit.header.uid = __get_next_uid(); 
	for (int sent = 0; sent < length; sent += PACKET_DATA_SIZE) {
		pack.transmit.header.index = index++;
		pack.transmit.header.flags = PACKET_DATA;
		pack.data_size = (uint32_t)fmin(length - sent, PACKET_DATA_SIZE);
		if (length - sent <= PACKET_DATA_SIZE)
			pack.transmit.header.flags |= PACKET_FINAL;
		memmove(pack.transmit.data, data + sent, pack.data_size);
		if (rsics_transmit_packet(&pack, computer) == TRANSMIT_FAIL)
			success = 0;
	}
	return success == 0 ? TRANSMIT_SEND : TRANSMIT_FAIL;
}

enum transmit_response rsics_transmit_packet(struct packet * packet,
					     struct connection * to_computer) {

	if (sendto(to_computer->file_descriptor, (void *)&packet->transmit,
		   sizeof(packet->transmit.header) + packet->data_size, 0,
		   (struct sockaddr *)&to_computer->socket_address,
		   to_computer->socket_address_size) == -1) {
		return TRANSMIT_FAIL;
	}

	return TRANSMIT_SEND;
}
