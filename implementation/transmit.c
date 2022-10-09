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


// MARK: - transmit_pakcet

void transmit_packet(struct Packet * packet, struct Computer * to_computer) {
	printf("%i, %i", (int)(sizeof(packet->transmitable_data) - PACKET_DATA_SIZE) + packet->data_size, packet->data_size);
	sendto(
	   to_computer->file_descriptor,
	   (void *)&((*packet).transmitable_data),
	   (sizeof(packet->transmitable_data) - PACKET_DATA_SIZE) + packet->data_size,
	   0,
	   (struct sockaddr *)&to_computer->socket_address,
	   to_computer->socket_address_size
   );
	
}

