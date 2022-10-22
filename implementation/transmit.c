//
//  transmit.c
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 01/10/2022.
//

#include "../definition/transmit.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <math.h>

// MARK: - fragment_into_packets
static PACKET_ID_SIZE current_index = 0;

static PACKET_ID_SIZE _get_next_id() {
	int index = current_index;
	current_index = (current_index + 1) % MAX_PACKET_ID;
	return index;
}

enum TransmitResponse ping(struct Computer * computer) {
	struct Packet ping_packet = {
		{
			{
				.index = 0,
				.uid = _get_next_id(),
				.options = 0b00000011,
			}
		},
		.data_size = 0
	};
	return _transmit_packet(&ping_packet, computer);
}


// TODO: - Error Handling
enum TransmitResponse transmit(const char * text, unsigned int length, struct Computer * computer) {
	
	char success = 1;
	struct Packet data_packet;
	PACKET_ID_SIZE current_uid = _get_next_id();
	printf("uid: %i\n", current_uid);
	for (int i = 0; i <= ceil( length / PACKET_DATA_SIZE ); i += 1) {
		data_packet.transmitable_data.header.index = i;
		data_packet.transmitable_data.header.uid = current_uid;
		data_packet.transmitable_data.header.options = length - (i * PACKET_DATA_SIZE) <= PACKET_DATA_SIZE ? 0b00000001 : 0b00000000;
		data_packet.data_size = (int)fmin(length - (i * PACKET_DATA_SIZE), PACKET_DATA_SIZE);
		memmove(&(data_packet.transmitable_data.data), &text[i * PACKET_DATA_SIZE], (int)fmin(length - (i * PACKET_DATA_SIZE), PACKET_DATA_SIZE));
		if (_transmit_packet(&data_packet, computer) == TRANSMIT_FAIL) {
			success = 0;
		};
	}
	return success ? TRANSMIT_SEND : TRANSMIT_FAIL;
}



// MARK: - transmit_pakcet
enum TransmitResponse _transmit_packet(struct Packet * packet, struct Computer * to_computer) {
	if (sendto(
		to_computer->file_descriptor,
		(void *)&((*packet).transmitable_data),
		sizeof(packet->transmitable_data.header) + packet->data_size,
		0,
		(struct sockaddr *)&to_computer->socket_address,
		to_computer->socket_address_size
	) == -1) {
		return TRANSMIT_FAIL;
	}
	
	return TRANSMIT_SEND;
	
}

