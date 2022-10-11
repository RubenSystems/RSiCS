//
//  transmit.h
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 01/10/2022.
//

#ifndef transmit_h
#define transmit_h

#include "models.h"

void ping(struct Computer *);

void transmit(const char *, unsigned int, struct Computer *);

void _transmit_packet(struct Packet *, struct Computer *);

#endif /* transmit_h */
