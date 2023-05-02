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

enum transmit_response { TRANSMIT_FAIL, TRANSMIT_SEND };

enum transmit_response transmit_packet(struct packet * packet,
				       struct connection * to_computer);

#endif /* transmit_h */
