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


// Attach event listener

void observe_with_context(struct Computer *, char *, const void *, void (*recieved_message)(const void *, struct Computer, void *, int));

void observe(struct Computer *, char *, void (*recieved_message)(const void *, struct Computer, void *, int));

enum ObserveResponse _recieve_packet(struct Packet *, struct Computer *, struct Computer *);

#endif /* observe_h */
