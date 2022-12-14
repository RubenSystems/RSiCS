//
//  config.h
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 30/09/2022.
//

#ifndef config_h
#define config_h

#include <limits.h>
#include <stdint.h>


/*
	Define the index size. Currently set to a char.
	That means that the maximum number of packets for a message is 11111111 or 255 pakcets.
	If your implementation requires more than 255 packets, consider changing to unsigned short.
	This would support 65535 packets.
*/
 
#define PACKET_INDEX_SIZE uint8_t


/*
	Each packet is assigned an ID for reconstruction. IDs are given incrementally e.g
 
		packet1: 0
		packet2: 1
		packet3: 2
 
	255 is generally a good number as this effectivley is the number of packets that can be processed by the system.
*/
#define PACKET_ID_SIZE uint8_t

#define MAX_PACKET_ID UCHAR_MAX


/*
	Each packet comes with options. some option indexes are reserved.
	
		bit 0: (the least significatn bit) determines if it is the last packet in a message.
		bit 1: is used for ping/pong message recieving.
 
	Any other bits are available. If you require more options, change this to a short
		
*/
#define PACKET_OPTION_SIZE uint8_t


/*
	The maximum transmission unit minus (ethernet, ip, udp, and checksum). Edit this if yours is smaller or bigger as RSiCS should handle
	fragmentation, not the system. Size is in bytes.
*/
#define MTU 1468

/*
	The amount of data that should be sent with the packet in bytes.
*/
#define PACKET_DATA_SIZE (MTU - (sizeof(PACKET_INDEX_SIZE) + sizeof(PACKET_ID_SIZE) + sizeof(PACKET_OPTION_SIZE)))


/*

	The maximum number of packets that can be recieved per message
	(if recieving 200, that is MTU (1472) * MAX_PACKETS_IN_FRAME (1472) = 294,400 bytes)
	The maximum value of this number is the the maximum of an unsigned char. 
 
 */

#define MAX_PACKETS_IN_FRAME 70


/*

	the maximum size of the unfragmented content that can be sent.
 
 */
#define MAX_CONTENT_SIZE PACKET_DATA_SIZE * MAX_PACKETS_IN_FRAME


/*
	frame pool is the maximum number of incomplete frames allowed 
 */
#define FRAME_POOL_SIZE 5




/*
 The number of tasks that the dispatcher can do simultaniously.
 */
#define DISPATCHER_TASK_SIZE 10

#endif /* config_h */
