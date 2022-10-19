//
//  frame.c
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 15/10/2022.
//

#include "../definition/frame.h"

void init_pool(struct FramePool * pool) {
	pool->latest_complete_frame = -1;
	for (unsigned int i = 0; i < sizeof(pool->frames) / sizeof(struct Frame); i ++) {
		pool->frames[i].frame_id = -1;
	}
}

void init_frame(struct Frame * frame, struct Packet * first_packet) {
	frame->recieved_packets = 1;
	frame->packets[first_packet->transmitable_data.index] = *first_packet;
	frame->frame_id = first_packet->transmitable_data.uid;
}

signed int add_packet_to(struct FramePool * pool, struct Packet * packet) {
	signed int last_available_slot = -1;
	for (unsigned int i = 0; i < sizeof(pool->frames) / sizeof(struct Frame); i ++) {
		if (pool->frames[i].frame_id == packet->transmitable_data.uid) {
			pool->frames[i].packets[packet->transmitable_data.index] = *packet;
			
			if ((packet->transmitable_data.options & 0b00000001) == 0b00000001) {
				// is completion packet
				pool->frames[i].required_packets = packet->transmitable_data.index;
			}
			
			return (pool->frames[i].required_packets == ++pool->frames[i].recieved_packets) ? i : FRAME_INSERTED;
		} else if (pool->frames[i].frame_id == -1) {
			last_available_slot = i;
		}
	}
	
	if (last_available_slot == -1) {
		return FRAME_FULL;
	}
	 
	init_frame(&(pool->frames[last_available_slot]), packet);
	return FRAME_INSERTED;
}
