//
//  buffer.c
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 30/04/2023.
//

#include "include/buffer.h"
#include <string.h>
void rsics_init_buffer(struct buffer * buffer) {
	memset(buffer->data.buffer, 0, sizeof(buffer->data.buffer));
	rsics_reset_buffer(buffer);
	pthread_mutex_init(&buffer->metadata.mutex, NULL);

	pthread_mutex_init(&buffer->data.mutex, NULL);
}

/*
 Assumes:
	- you already have a lock on the metadata
 */
enum buffer_add_response rsics_add_to_buffer(struct buffer * buf,
					     struct packet * packet) {
	//	unlocked below
	memmove(&buf->data.buffer[PACKET_DATA_SIZE *
				  packet->transmit.header.index],
		packet->transmit.data, packet->data_size);

	// unlocked in both exit conditions
	buf->metadata.recieved_packets++;
	buf->metadata.data_count += packet->data_size;
	if (packet->transmit.header.flags & PACKET_FINAL)
		buf->metadata.required_packets = packet->transmit.header.index;

	if (buf->metadata.required_packets != -1 &&
	    buf->metadata.recieved_packets >= buf->metadata.required_packets) {
		return BUFFER_COMPLETE;
	} else {
		return BUFFER_INCOMPLETE;
	}
}

void rsics_open_read_session(struct buffer * buf) {
	buf->metadata.read_available = false;
}

void rsics_reset_buffer(struct buffer * buf) {
	buf->metadata.frame_id = -1;
	buf->metadata.recieved_packets = 0;
	buf->metadata.required_packets = 0;
	buf->metadata.data_count = 0;
	buf->metadata.read_available = true;
}

void rsics_destroy_buffer_session(struct buffer * buf) {
	rsics_reset_buffer(buf);
}
