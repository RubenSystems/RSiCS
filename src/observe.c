//
//  observe.c
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 06/10/2022.
//

#include "include/observe.h"
#include "include/frame.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>


static signed int _handle_new_frame(struct FramePool *, struct Packet *);

static void merge_frames_to_buffer(struct ContentBuffer *, int, const struct FramePool *, const void *, struct Computer, message_callback);

static uint8_t __get_sa_len(struct sockaddr * address) {
	switch (address->sa_family) {
		case AF_INET:
			return sizeof(struct sockaddr_in);
		case AF_INET6:
			return sizeof(struct sockaddr_in6);
	}
	return 0;
}

void observe_with_context(struct Computer * listener, char * is_active, const void * context, message_callback recieved_message) {
	struct ContentBuffer buffer;
	struct FramePool * pool = malloc(sizeof(struct FramePool));
	init_pool(pool);
	int complete_frame_index;
	while (*is_active == 1) {
		struct Packet from_packet;
		struct Computer from_computer;
		_recieve_packet(&from_packet, listener, &from_computer);
		
		if ((complete_frame_index = _handle_new_frame(pool, &from_packet)) >= 0) {
			merge_frames_to_buffer(&buffer, complete_frame_index, pool, context, from_computer, recieved_message);
		}
		
	}
	free(pool);
}


void observe(struct Computer * listener, char * is_active, message_callback callback) {
	observe_with_context(listener, is_active, NULL, callback);
}


static void merge_frames_to_buffer(
								   struct ContentBuffer *buffer,
								   int complete_frame_index,
								   const struct FramePool *pool,
								   const void * context,
								   struct Computer from_computer,
								   message_callback recieved_message
								) {
	memset((void *)&(buffer->data), 0, sizeof(buffer->data) / sizeof(char));
	int frame_size = 0;
	printf("%i %i\n", pool->frames[complete_frame_index].required_packets, pool->frames[complete_frame_index].recieved_packets);
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
	recieved_message(context, &from_computer, buffer->data, frame_size + 1);
}

// Returns 0 if no action is required. Else it will the index of the packet to return
static signed int _handle_new_frame(struct FramePool * pool, struct Packet * packet) {
	int packet_index = add_packet_to(pool, packet);
	switch (packet_index) {
		case FRAME_FULL:
			init_pool(pool);
			return _handle_new_frame(pool, packet);
		case FRAME_INSERTED:
			return -1;
		default:
			return packet_index;
	}
}

enum ObserveResponse _recieve_packet(struct Packet * packet, struct Computer * recieve_listener, struct Computer * from_computer) {
	struct sockaddr_storage storage;
	socklen_t storage_size = sizeof(struct sockaddr_storage);
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
	from_computer->socket_address = *(struct sockaddr *)&storage;
	from_computer->socket_address_size = __get_sa_len(&from_computer->socket_address);
	return ((packet->transmitable_data.header.options & 0b00000010) == 0b00000010) ? OBSERVE_PONG : OBSERVE_DATA;
}

