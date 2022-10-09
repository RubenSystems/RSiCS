//
//  observe.c
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 06/10/2022.
//

#include "../definition/observe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>

void recieve_packet(struct Packet * packet, struct Computer * recieve_listener, struct Computer * from_computer) {

	char tempbuf [1000];
	memset(&tempbuf, 0, 1000);
	struct sockaddr_storage storage;
	socklen_t storage_size = sizeof(storage);
	if (recvfrom(
		recieve_listener->file_descriptor,
		&(packet->receveable_data),
		MTU,
		0,
		(struct sockaddr *)&storage,
		 &storage_size
	 ) == -1) {
		 perror("recvfrom");
	 }
	
	for (int i = 0; i < 1000; i ++) {
		printf("%c", tempbuf[i]);
	}
	
	
	
	from_computer->file_descriptor = recieve_listener->file_descriptor;
}
