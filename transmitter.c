//
//  transmitter.c
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 07/10/2022.
//

#include <stdio.h>
#include <stdlib.h>

#include "definition/transmit.h"
//#include "definition/observe.h"


int main(int argc, const char * argv[]) {
	// This is an example of how you create a computer (something to send data to) and then send messages to it. 

	struct Computer * computer = create_computer("localhost", "5253");
	transmit("hello there my name is ruben and i am cool!", 43, &computer);
	free(computer);
	return 0;
}

