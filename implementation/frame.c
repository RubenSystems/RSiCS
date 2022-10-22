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
	frame->recieved_packets = 0;
	frame->required_packets = -1;
	frame->frame_id = first_packet->transmitable_data.header.uid;
}

static int move_packet_to_frame(struct Packet *packet, struct Frame * frame) {
	frame->packets[packet->transmitable_data.header.index] = *packet;
	
	if ((packet->transmitable_data.header.options & 0b00000001) == 0b00000001) { // Completion check
		frame->required_packets = packet->transmitable_data.header.index;
	}
	char cond = (frame->required_packets + 1 < ++frame->recieved_packets);
	frame->frame_id = -1; 
	return cond ? FRAME_INSERTED : FRAME_COMPLETE;
}

signed int add_packet_to(struct FramePool * pool, struct Packet * packet) {
	signed int last_available_slot = -1;
	for (unsigned int i = 0; i < sizeof(pool->frames) / sizeof(struct Frame); i ++) {
		if (pool->frames[i].frame_id == packet->transmitable_data.header.uid) {
			int mv = move_packet_to_frame(packet, &(pool->frames[i])) ;
			return mv == FRAME_COMPLETE ? i : FRAME_INSERTED;
		} else if (pool->frames[i].frame_id == -1) {
			last_available_slot = i;
		}
	}
	
	if (last_available_slot == -1) {
		return FRAME_FULL;
	}
	 
	init_frame(&(pool->frames[last_available_slot]), packet);
	int mv = move_packet_to_frame(packet, &(pool->frames[last_available_slot]));
	return mv == FRAME_COMPLETE ? last_available_slot : FRAME_INSERTED;
}
