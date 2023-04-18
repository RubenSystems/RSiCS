//
//  transmit.h
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 01/10/2022.
//

#ifndef transmit_h
#define transmit_h

#include "models.h"

#ifdef __cplusplus
extern "C" {
#endif

enum TransmitResponse {
	TRANSMIT_FAIL,
	TRANSMIT_SEND
};

enum TransmitResponse ping(struct Computer *);

enum TransmitResponse transmit(void *, unsigned int, struct Computer *);

enum TransmitResponse transmit_packet(struct Packet *, struct Computer *);

#ifdef __cplusplus
}
#endif

#endif /* transmit_h */
