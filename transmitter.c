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
	// insert code here...
//	struct Packet x = {
//		{
//			.index = 0,
//			.uid = 0,
//			.options = 0b00000000,
//			.data = "hello"
//
//		},
//		.data_size = 5
//	};
	struct Computer * computer = create_computer("localhost", "5253");
	transmit("hello there my name is ruben and i am cool!", 43, &computer);
	free(computer);
	return 0;
}

