//
//  transmit.h
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 01/05/2023.
//

#ifndef transmit_h
#define transmit_h

#include <stdio.h>
#include "packet.h"
#include "connection.h"

#ifdef __cplusplus
extern "C" {
#endif

enum transmit_response { TRANSMIT_FAIL, TRANSMIT_SEND };

enum transmit_response rsics_ping(struct connection * to_computer,
				  const char * session_token);

enum transmit_response rsics_transmit(void * data, uint64_t length,
				      struct connection * computer);

enum transmit_response rsics_transmit_packet(struct packet * packet,
					     struct connection * to_computer);

#ifdef __cplusplus
}
#endif

#endif /* transmit_h */
