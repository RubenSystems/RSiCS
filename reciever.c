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


int main(int argc, const char * argv[]) {
	// This is an example of how you set up a listener and start recieving packets on that listener
	struct Computer * listener = create_listener("5253");
	struct Computer recieved_from;
	struct Packet recieved_packet;
	recieve_packet(&recieved_packet, listener, &recieved_from);
	printf("%s - ", recieved_packet.transmitable_data.data);
	free(listener);
	
	return 0;
}
