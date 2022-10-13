//
//  transmit.h
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 01/10/2022.
//

#ifndef transmit_h
#define transmit_h

#include "models.h"


enum TransmitResponse {
	TRANSMIT_FAIL,
	TRANSMIT_SEND
};

enum TransmitResponse ping(struct Computer *);

enum TransmitResponse transmit(const char *, unsigned int, struct Computer *);

enum TransmitResponse _transmit_packet(struct Packet *, struct Computer *);

#endif /* transmit_h */
