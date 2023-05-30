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
#include <string.h>
#include <err.h>

void rsics_init_pool(struct buffer_pool * pool) {
	pool->active = malloc(sizeof(struct buffer));
	rsics_init_buffer(pool->active);
	
	pool->running = malloc(sizeof(struct buffer *) * BUFFER_POOL_SIZE);
	for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
		pool->running[i] = malloc(sizeof(struct buffer));
		rsics_init_buffer(pool->running[i]);
	}
		
}

void rsics_close_pool(struct buffer_pool * pool) {
	free(pool->active);
	
	for (int i = 0; i < BUFFER_POOL_SIZE; i ++)
		free(pool->running[i]);
	
	free(pool->running);
}

static uint16_t reset_buffers(struct buffer_pool * pool) {
	int16_t latest_available_buffer = -1;
	for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
		rsics_reset_buffer(pool->running[i]);
		latest_available_buffer = i;
	}

	return latest_available_buffer;
}

static void flip_buffer(struct buffer ** a, struct buffer ** b) {
	struct buffer * tmp = *a;
	*a = *b;
	*b = tmp;
}

bool rsics_pool_add_packet(struct buffer_pool * pool,
			      struct packet * packet) {
	int16_t latest_available_frame = -1;
	for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
		// if pool id == packet id and adding to the buffer makes it complete
		if (pool->running[i]->metadata.frame_id ==
		    packet->transmit.header.uid) {
			if (rsics_add_to_buffer(pool->running[i], packet) ==
			    BUFFER_COMPLETE) {
				flip_buffer(&pool->active, &pool->running[i]);
				return true;
			} else {
				return false;
			}
		} else if (latest_available_frame == -1) {
			latest_available_frame = i;
		}
	}

	if (latest_available_frame == -1 &&
	    (latest_available_frame = reset_buffers(pool)) == -1) {
		perror("[RSICS] - no available buffers");
		exit(-1);
	}

	// Could not find a buffer, initalise a new one
	struct buffer * buf = pool->running[latest_available_frame];
	rsics_reset_buffer(buf);
	buf->metadata.frame_id = packet->transmit.header.uid;
	if (rsics_add_to_buffer(buf, packet) == BUFFER_COMPLETE) {
		flip_buffer(&pool->active, &pool->running[latest_available_frame]);
		return true;
	}

	return false;
}

