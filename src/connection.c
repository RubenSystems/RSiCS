//
//  connection.c
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 29/04/2023.
//

#include "include/connection.h"
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

struct connection * rsics_init_connection() {
	return malloc(sizeof(struct connection));
}

enum create_listener_response rsics_connect(const char * ip, const char * port,
					    struct connection * computer) {
	int fd = 0, rv;
	struct addrinfo hints, *servinfo, *p;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(ip, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return CREATE_LISTENER_FAIL;
	}

	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((fd = socket(p->ai_family, p->ai_socktype,
				 p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}
		break;
	}

	computer->file_descriptor = fd;
	computer->socket_address = *(p->ai_addr);
	computer->socket_address_size = p->ai_addrlen;
	freeaddrinfo(servinfo);

	return CREATE_LISTENER_SUCCEED;
}

enum create_listener_response
rsics_make_listener(const char * port, struct connection * computer) {
	int fd = 0, rv;
	struct addrinfo *server_info, *p, hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, port, &hints, &server_info)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return CREATE_LISTENER_FAIL;
	}

	for (p = server_info; p != NULL; p = p->ai_next) {
		if ((fd = socket(p->ai_family, p->ai_socktype,
				 p->ai_protocol)) == -1) {
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
		return CREATE_LISTENER_FAIL;
	}

	computer->file_descriptor = fd;
	computer->socket_address = *(p->ai_addr);
	computer->socket_address_size = (p->ai_addrlen);

	freeaddrinfo(server_info);

	return CREATE_LISTENER_SUCCEED;
}

void rsics_free_connection(struct connection * computer) {
	free(computer);
}
