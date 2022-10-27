//
//  reciever.c
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 07/10/2022.
//

#include <stdio.h>
#include <stdlib.h>

//#include "definition/transmit.h"
#include "definition/observe.h"


static void recieved_message(void *ctx, const char * message, int message_size) {
	printf("-%s-\n\n", message);
}

int main(int argc, const char * argv[]) {
	// This is an example of how you set up a listener and start recieving packets on that listener
	struct Computer listener;
	struct Computer from;
	struct Packet pack;
	create_listener("5253", &listener);
//
	char is_active = 1;
	int context = 100;
//
	observe(&listener, &is_active, recieved_message);
//	_recieve_packet(&pack, &listener, &from);

	return 0;
}
