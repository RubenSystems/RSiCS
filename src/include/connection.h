//
//  connection.h
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 29/04/2023.
//

#ifndef connection_h
#define connection_h

#include <stdio.h>
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

	struct connection {
		int 				file_descriptor;
		struct sockaddr 	socket_address;
		socklen_t 			socket_address_size;
	};
	
	/*
	 Create an empty connection
	 */
	struct connection *
	rsics_init_connection(void);
	
	/*
	 Create listeners
	 */
	enum create_listener_response {
		CREATE_LISTENER_FAIL,
		CREATE_LISTENER_SUCCEED
	};
	
	enum create_listener_response
	rsics_connect(
		const char * ip,
		const char * port,
		struct connection *
	);
	
	enum create_listener_response
	rsics_listen(
		const char * port,
		struct connection *
	);
	
	void
	rsics_free_connection(
	  struct connection *
	);
	
	
	

	
#ifdef __cplusplus
}
#endif

#endif /* connection_h */
