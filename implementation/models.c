//
//  models.c
//  RSiCS
//
//  Created by Ruben Ticehurst-James on 06/10/2022.
//

#include "../definition/models.h"

#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct Computer * create_computer(const char * ip, const char * port) {
	int fd = 0, rv;
	struct addrinfo hints, *servinfo, *p;
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	
	if ((rv = getaddrinfo(ip, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return NULL;
	}
	
	
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}
		break;
	}
	
	struct Computer * computer = (struct Computer *)malloc(sizeof(struct Computer));
	
	struct Computer ret_computer = {
		.file_descriptor = fd,
		.socket_address = *(p->ai_addr),
		.socket_address_size = p->ai_addrlen
	};
		
	*computer = ret_computer;
	
	return computer;
}


struct Computer * create_listener(const char * port) {
	int fd = 0, rv;
	struct addrinfo * server_info, *p, hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	
	if ((rv = getaddrinfo(NULL, port, &hints, &server_info)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return NULL;
	}
	 
	for(p = server_info; p != NULL; p = p->ai_next) {
		if ((fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}

		if (bind(fd, p->ai_addr, p->ai_addrlen) == -1) {
			close(fd);
			perror("listener: bind");
			continue;
		}
		
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		return NULL;
	}

	struct Computer * computer = (struct Computer *)malloc(sizeof(struct Computer));
	
	struct Computer ret_computer = {
		.file_descriptor = fd,
		.socket_address = *(p->ai_addr),
		.socket_address_size = (p->ai_addrlen)
	};
	

	*computer = ret_computer;
	
	freeaddrinfo(server_info);
	
	return computer;
	
}
