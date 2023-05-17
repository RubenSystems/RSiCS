//
//  buffer.h
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 29/04/2023.
//

#ifndef buffer_h
#define buffer_h

#include "config.h"
#include "packet.h"

#include <pthread.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct buffer {
	struct {
		uint32_t recieved_packets;
		int32_t required_packets;
		int32_t frame_id;
		uint64_t data_count;
	} metadata;

	struct {
		char buffer[MAX_PACKETS_IN_BUFFER *
			    (MTU - sizeof(struct packet_header))];
	} data;
};

void rsics_init_buffer(struct buffer *);

/*
	 Adding to buffer
	 */

enum buffer_add_response { BUFFER_COMPLETE = 1, BUFFER_INCOMPLETE = 0 };

enum buffer_add_response rsics_add_to_buffer(struct buffer *, struct packet *);

void rsics_open_read_session(struct buffer *);

void rsics_reset_buffer(struct buffer *);

void rsics_destroy_buffer_session(struct buffer *);

#ifdef __cplusplus
}
#endif

#endif /* buffer_h */
