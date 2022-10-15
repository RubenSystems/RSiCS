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

#include <stdio.h>


enum FrameInsertResponse {
	FRAME_FULL,
	FRAME_INSERTED,
	FRAME_COMPLETE
};

struct Frame {
	struct Packet 	packets	[MAX_PACKETS_IN_FRAME];
	int 			recieved_packets; // The number of packets that have been recieved.
	int 			required_packets; // The number of packets required to fill the frame 100%
	signed int		frame_id; //Want signed so -1 ccan be invalid. 
};

struct FramePool {
	struct Frame	frames [FRAME_POOL_SIZE];
};

void init_pool(struct FramePool *);

void init_frame(struct Frame *, struct Packet *);

enum FrameInsertResponse add_packet_to(struct FramePool *, struct Packet *);

#endif /* frame_h */
