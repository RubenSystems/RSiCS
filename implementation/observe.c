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

static unsigned int _handle_new_frame(struct FramePool *, struct Packet *);

static void merge_frames_to_buffer(struct ContentBuffer *, int, const struct FramePool *, void (*recieved_message)(const char *, int));



void observe(struct Computer * listener, char * is_active, void (*recieved_message)(const char *, int)) {
	struct ContentBuffer buffer;
	struct FramePool pool;
	init_pool(&pool); 
	int complete_frame_index;
	while (*is_active == 1) {
		struct Packet from_packet;
		struct Computer from_computer;
		_recieve_packet(&from_packet, listener, &from_computer);
		if ((complete_frame_index = _handle_new_frame(&pool, &from_packet)) > 0) {
			merge_frames_to_buffer(&buffer, complete_frame_index, &pool, recieved_message);
		}
	}
}


static void merge_frames_to_buffer(struct ContentBuffer *buffer, int complete_frame_index, const struct FramePool *pool, void (*recieved_message)(const char *, int)) {
	memset((void *)&(buffer->data), 0, sizeof(buffer->data) / sizeof(char));
	int frame_size = 0;
	for (unsigned int i = 0; i <= pool->frames[complete_frame_index].recieved_packets; i ++) {
		struct Packet * packet = (void *)&(pool->frames[complete_frame_index].packets[i]);
		memmove(
				(void *)&(buffer->data[frame_size]),
				packet->transmitable_data.data,
				packet->data_size
		);
		frame_size += packet->data_size;
	}
	buffer->data[frame_size + 1] = 0;
	recieved_message(buffer->data, frame_size + 1);
}

// Returns 0 if no action is required. Else it will the index of the packet to return
static unsigned int _handle_new_frame(struct FramePool * pool, struct Packet * packet) {
	int packet_index = add_packet_to(pool, packet);
	switch (packet_index) {
		case FRAME_FULL:
			init_pool(pool);
			return _handle_new_frame(pool, packet);
		case FRAME_INSERTED:
			return 0;
		default:
			return packet_index;
	}
}

enum ObserveResponse _recieve_packet(struct Packet * packet, struct Computer * recieve_listener, struct Computer * from_computer) {
	struct sockaddr_storage storage;
	socklen_t storage_size = sizeof(storage);
	int data_size;
	if ((data_size = (int)recvfrom(
		recieve_listener->file_descriptor,
		(void *)&(packet->transmitable_data),
		MTU,
		0,
		(struct sockaddr *)&storage,
		 &storage_size
	)) == -1) {
		return OBSERVE_FAIL;
	}
	
	packet->data_size = data_size - sizeof(packet->transmitable_data.header);
	from_computer->file_descriptor = recieve_listener->file_descriptor;
	
	return ((packet->transmitable_data.header.options & 0b00000010) == 0b00000010) ? OBSERVE_PONG : OBSERVE_DATA;
}

