//
//  config.h
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 29/04/2023.
//

#ifndef config_h
#define config_h

#include <limits.h>
#include <stdint.h>

#define PACKET_INDEX_SIZE uint16_t

#define PACKET_ID_SIZE uint8_t

#define MAX_PACKET_ID UCHAR_MAX

#define MTU 1468

#define MAX_PACKETS_IN_BUFFER 70

#define BUFFER_POOL_SIZE 5

#endif /* config_h */
