//
//  buffer_pool.h
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 30/04/2023.
//

#ifndef buffer_pool_h
#define buffer_pool_h

#include <stdio.h>
#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

struct buffer_pool {
	struct buffer * buffers;
};

void rsics_init_pool(struct buffer_pool *);

void rsics_close_pool(struct buffer_pool *);

int16_t rsics_pool_add_packet(struct buffer_pool *, struct packet * packet);

#ifdef __cplusplus
}
#endif

#endif /* buffer_pool_h */
