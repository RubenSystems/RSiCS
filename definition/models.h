//
//  models.h
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 30/09/2022.
//

#ifndef models_h
#define models_h

#include "../config.h"

#include <sys/socket.h>


/*
	MARK: - Packet
	Several packets make a frame.
	A frame is the data which is being sent.
 
	A packet has an index. This is the index in the frame that the packet is in.
		- As an example a frame may have 23 packet. If a packet index is 10, that means it is packet 10 out of 23.
		- Packets are zero indexed
 
	Packets also have an id. This is the id of the frame which the packet belongs to.
	Packets have options. This is a small amount of data that act as instructions to the reciver. Options include:
		 - IF the packet is the final packet in the frame.
		 - If the packet is a ping packet (one which requires a pong).
 
	Finally, packets have data, and the size of the data.
		
*/
struct Packet {
	struct {
		PACKET_INDEX_SIZE 		index;
		PACKET_ID_SIZE 			uid;
		PACKET_OPTION_SIZE 		options;
		char 					data		[PACKET_DATA_SIZE];
	} transmitable_data;
	int 						data_size;
};



struct Computer {
	int 				file_descriptor;
	struct sockaddr 	socket_address;
	socklen_t 			socket_address_size;
};



enum AttachmentResponse {
	ATTACH_FAIL,
	ATTACH_SUCCESS
};

enum AttachmentResponse create_computer(const char *, const char *, struct Computer *);

enum AttachmentResponse create_listener(const char *, struct Computer *);


#endif /* models_h */
