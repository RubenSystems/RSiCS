//
//  config.h
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 30/09/2022.
//

#ifndef config_h
#define config_h

#include <limits.h>

/*
	Define the index size. Currently set to a char.
	That means that the maximum number of packets for a message is 11111111 or 255 pakcets.
	If your implementation requires more than 255 packets, consider changing to unsigned short.
	This would support 65535 packets.
*/
 
#define PACKET_INDEX_SIZE unsigned char


/*
	Each packet is assigned an ID for reconstruction. IDs are given incrementally e.g
 
		packet1: 0
		packet2: 1
		packet3: 2
 
	255 is generally a good number as this effectivley is the number of packets that can be processed by the system.
*/
#define PACKET_ID_SIZE unsigned char

#define MAX_PACKET_ID UCHAR_MAX


/*
	Each packet comes with options. some option indexes are reserved.
	
		bit 0: (the least significatn bit) determines if it is the last packet in a message.
		bit 1: is used for ping/pong message recieving.
 
	Any other bits are available. If you require more options, change this to a short
		
*/
#define PACKET_OPTION_SIZE unsigned char


/*
	The maximum transmission unit (ethernet frame). Edit this if yours is smaller or bigger as RSiCS should handle
	fragmentation, not the system. Size is in bytes.
*/
#define MTU 1480

/*
	The amount of data that should be sent with the packet in bytes.
*/
#define PACKET_DATA_SIZE (MTU - (sizeof(PACKET_INDEX_SIZE) + sizeof(PACKET_ID_SIZE) + sizeof(PACKET_OPTION_SIZE)))

#endif /* config_h */
