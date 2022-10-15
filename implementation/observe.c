//
//  observe.c
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 06/10/2022.
//

#include "../definition/observe.h"
#include "../definition/frame.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>


void observe(struct Computer * listener, void (*recieved_message)(int)) {
	
	struct FramePool pool;
	init_pool(&pool); 
	
	while (1) {
		struct Packet from_packet;
		struct Computer from_computer;
		
		_recieve_packet(&from_packet, listener, &from_computer);
		switch (add_packet_to(&pool, &from_packet)) {
				
			case FRAME_FULL:
				init_pool(&pool);
				// TODO: - Recursivly add it in to stop wasting a frame
				break;
			case FRAME_INSERTED:
				break;
			case FRAME_COMPLETE:
				// TODO: - figure out which frame is complete and complete
				break;
		}
	}
	
}

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
