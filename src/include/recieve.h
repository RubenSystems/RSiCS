//
//  recieve.h
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 01/05/2023.
//

#ifndef recieve_h
#define recieve_h

#include <stdio.h>
#include <stdbool.h>

#include "connection.h"
#include "packet.h"
#include "buffer_pool.h"
#include "lambda.h"

#ifdef __cplusplus
extern "C" {
#endif

enum recieve_response { RECIEVE_FAIL, RECIEVE_DATA, RECIEVE_PING };

enum message_type { MESSAGE_DATA, MESSAGE_ERR, MESSAGE_PING };

lambda_defs(void, message_callback, struct connection *, enum message_type,
	    void *, uint64_t);

void rsics_listen(struct connection *, bool *, struct message_callback);

enum recieve_response rsics_recieve_once(struct connection *, struct packet *,
					 struct connection *);

#ifdef __cplusplus
}
#endif

#endif /* recieve_h */
