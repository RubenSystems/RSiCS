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


void
rsics_init_pool(struct buffer_pool * pool) {
	pool->buffers = malloc(sizeof(struct buffer) * BUFFER_POOL_SIZE);
}

void
rsics_close_pool(struct buffer_pool * pool) {
	free(pool->buffers);
}

uint16_t
rsics_add_packet(struct buffer_pool *) {
	
}
