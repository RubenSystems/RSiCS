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


// MARK: - fragment_into_packets
void transmit(const char * text, unsigned int length, struct Computer * computer) {
	for (int offset = 0; offset < length; offset += PACKET_DATA_SIZE) {
		
		struct Packet data_packet = {
			{
				.index = offset,
				.uid = offset,
				.options = length - (offset * PACKET_DATA_SIZE) <= PACKET_DATA_SIZE ? 0b00000001 : 0b00000000,

			},
			.data_size = length - (offset * PACKET_DATA_SIZE)
		};
		memmove(data_packet.transmitable_data.data, text + (offset * PACKET_DATA_SIZE), PACKET_DATA_SIZE);
		printf("%i\n", data_packet.transmitable_data.options);
		transmit_packet(&data_packet, computer);
	}
}

// MARK: - transmit_pakcet
void transmit_packet(struct Packet * packet, struct Computer * to_computer) {
//	printf("%i, %i", (int)(sizeof(packet->transmitable_data) - PACKET_DATA_SIZE) + packet->data_size, packet->data_size);
	sendto(
	   to_computer->file_descriptor,
	   (void *)&((*packet).transmitable_data),
	   (sizeof(packet->transmitable_data) - PACKET_DATA_SIZE) + packet->data_size,
	   0,
	   (struct sockaddr *)&to_computer->socket_address,
	   to_computer->socket_address_size
   );
	
}

