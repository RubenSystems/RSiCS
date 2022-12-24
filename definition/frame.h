//
//  frame.h
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 15/10/2022.
//

#ifndef frame_h
#define frame_h

#include "../config.h"
#include "models.h"



enum FrameInsertResponse {
	FRAME_FULL = -3,
	FRAME_INSERTED = -2,
	FRAME_COMPLETE = -1
};

struct Frame {
	struct Packet 	packets	[MAX_PACKETS_IN_FRAME];
	unsigned int 	recieved_packets; // The number of packets that have been recieved.
	signed int 		required_packets; // The number of packets required to fill the frame 100%, -1 if not known 
	signed int		frame_id; //Want signed so -1 ccan be invalid.
};

struct FramePool {
	struct Frame	frames [FRAME_POOL_SIZE];
	signed int		latest_complete_frame;
};

void init_pool(struct FramePool *);

void init_frame(struct Frame *, struct Packet *);

signed int add_packet_to(struct FramePool *, struct Packet *);

#endif /* frame_h */
