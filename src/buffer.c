//
//  buffer.c
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 30/04/2023.
//

#include "include/buffer.h"
#include <string.h>
void
rsics_init_buffer(
	struct buffer * buffer
) {
	memset(buffer->data.buffer, 0, sizeof(buffer->data.buffer));
	buffer->metadata.recieved_packets = 0;
	buffer->metadata.required_packets = 0;
	buffer->metadata.frame_id = -1;
	
	pthread_mutex_init(
		&buffer->metadata.mutex,
		NULL
	);
	
	pthread_mutex_init(
		&buffer->data.mutex,
		NULL
	);

}


enum buffer_add_response
rsics_add_to_buffer(
			  struct buffer * buf ,
			  struct packet * packet
	) {
	memmove(
			&buf->data.buffer[PACKET_DATA_SIZE * packet->transmit.header.index],
			packet->transmit.data,
			packet->data_size
		);
	pthread_mutex_lock(&buf->mutex);
	buf->recieved_packets++;
	if (packet->transmit.header.flags & PACKET_FINAL)
		buf->required_packets = packet->transmit.header.index;
	pthread_mutex_unlock(&buf->mutex);
	
	// if buf has a complete number of packets
	if( buf->required_packets != -1 &&
	   buf->recieved_packets >= buf->required_packets) {
		return BUFFER_COMPLETE;
	}
	
	return BUFFER_INCOMPLETE;
}

void
rsics_open_read_session(
					struct buffer * buf
					   ) {
	pthread_mutex_lock(&buf->mutex);
}

void rsics_reset_buffer(
					struct buffer * buf
				  ){
	buf->frame_id = -1;
	buf->recieved_packets = 0;
	buf->required_packets = 0;
}

void rsics_destroy_buffer_session(
					struct buffer * buf
							) {
	rsics_reset_buffer(buf);
	pthread_mutex_unlock(&buf->mutex);
}
