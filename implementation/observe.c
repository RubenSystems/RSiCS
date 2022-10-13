//
//  observe.c
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 06/10/2022.
//

#include "../definition/observe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>

// TODO: - Error Handling
enum ObserveResponse _recieve_packet(struct Packet * packet, struct Computer * recieve_listener, struct Computer * from_computer) {
	struct sockaddr_storage storage;
	socklen_t storage_size = sizeof(storage);
	if (recvfrom(
		recieve_listener->file_descriptor,
		(void *)&(packet->transmitable_data),
		MTU,
		0,
		(struct sockaddr *)&storage,
		 &storage_size
	) == -1) {
		return OBSERVE_FAIL;
	}
	from_computer->file_descriptor = recieve_listener->file_descriptor;
	
	return ((packet->transmitable_data.options & 0b00000010) == 0b00000010) ? OBSERVE_PONG : OBSERVE_DATA;
}
