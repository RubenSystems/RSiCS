//
//  observe.h
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 06/10/2022.
//

#ifndef observe_h
#define observe_h

#include "models.h"


enum ObserveResponse {
	OBSERVE_FAIL,
	OBSERVE_PONG,
	OBSERVE_DATA
};

enum ObserveResponse _recieve_packet(struct Packet *, struct Computer *, struct Computer *);

#endif /* observe_h */
