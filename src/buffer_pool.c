//
//  buffer_pool.c
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 30/04/2023.
//

#include "include/buffer_pool.h"
#include "include/buffer.h"
#include "include/config.h"
#include <stdlib.h>
#include <err.h>

void rsics_init_pool(struct buffer_pool * pool) {
	pool->buffers = malloc(sizeof(struct buffer) * BUFFER_POOL_SIZE);
}

void rsics_close_pool(struct buffer_pool * pool) {
	free(pool->buffers);
}

static uint16_t reset_buffers(struct buffer_pool * pool) {
	int16_t latest_available_buffer = -1;
	for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
		if (pool->buffers[i].metadata.read_available) {
			rsics_reset_buffer(&pool->buffers[i]);
			latest_available_buffer = i;
		}
	}

	return latest_available_buffer;
}

int16_t rsics_pool_add_packet(struct buffer_pool * pool,
			      struct packet * packet) {
	int16_t latest_available_frame = -1;
	for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
		// if pool id == packet id and adding to the buffer makes it complete
		if (pool->buffers[i].metadata.frame_id ==
			    packet->transmit.header.uid &&
		    rsics_add_to_buffer(&pool->buffers[i], packet) ==
			    BUFFER_COMPLETE) {
			return i;
		} else if (pool->buffers[i].metadata.read_available) {
			latest_available_frame = i;
		}
	}

	if (latest_available_frame == -1 &&
	    (latest_available_frame = reset_buffers(pool)) == -1) {
		perror("[RSICS] - no available buffers");
		exit(-1);
	}

	// Could not find a buffer, initalise a new one
	struct buffer * buf = &pool->buffers[latest_available_frame];
	rsics_reset_buffer(buf);
	buf->metadata.frame_id = packet->transmit.header.uid;
	if (rsics_add_to_buffer(buf, packet) == BUFFER_COMPLETE) {
		return latest_available_frame;
	}

	return -1;
}
