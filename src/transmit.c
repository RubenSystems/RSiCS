//
//  transmit.c
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 01/05/2023.
//

#include "transmit.h"
#include <string.h>

enum transmit_response ping(struct connection * to_computer,
			    const char * session_token) {
	static struct packet_header header = {
		.index = 0, .flags = PACKET_FINAL | PACKET_PING
	};

	struct packet pack = { .transmit = { .header = header },
			       .data_size = strnlen(session_token,
						    PACKET_DATA_SIZE - 1) };

	return transmit_packet(&pack, to_computer);
}

enum transmit_response transmit_packet(struct packet * packet,
				       struct connection * to_computer) {
	static uint8_t uid = 0;

	uid = (uid + 1) / UCHAR_MAX;
	packet->transmit.header.uid = uid;

	if (sendto(to_computer->file_descriptor, (void *)&((*packet).transmit),
		   sizeof(packet->transmit.header) + packet->data_size, 0,
		   (struct sockaddr *)&to_computer->socket_address,
		   to_computer->socket_address_size) == -1) {
		return TRANSMIT_FAIL;
	}

	return TRANSMIT_SEND;
}
