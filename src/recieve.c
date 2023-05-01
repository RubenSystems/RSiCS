//
//  recieve.c
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 01/05/2023.
//

#include "include/recieve.h"
#include <netinet/in.h>

static uint8_t __get_sa_len(struct sockaddr * address) {
	switch (address->sa_family) {
	case AF_INET:
		return sizeof(struct sockaddr_in);
	case AF_INET6:
		return sizeof(struct sockaddr_in6);
	}
	return 0;
}

void rsics_listen(struct connection * conn, bool * listening,
		  struct message_callback callback) {
	struct buffer_pool pool;
	rsics_init_pool(&pool);
	struct packet latest_packet;
	struct connection latest_connection;
	while (*listening) {
		enum recieve_response r = rsics_recieve_once(
			conn, &latest_packet, &latest_connection);

		switch (r) {
		case RECIEVE_FAIL:
			callback.function(callback.context, &latest_connection,
					  MESSAGE_ERR, NULL, 0);
			break;
		case RECIEVE_DATA: {
			int r = rsics_pool_add_packet(&pool, &latest_packet);
			if (r != -1) {
				callback.function(
					callback.context, &latest_connection,
					MESSAGE_DATA,
					pool.buffers[r].data.buffer,
					pool.buffers[r].metadata.data_count);
			}
		} break;
		case RECIEVE_PING:
			callback.function(callback.context, &latest_connection,
					  MESSAGE_PING,
					  latest_packet.transmit.data,
					  latest_packet.data_size);
			break;
		}
	}
}

enum recieve_response rsics_recieve_once(struct connection * to,
					 struct packet * packet,
					 struct connection * from) {
	struct sockaddr_storage storage;
	socklen_t storage_size = sizeof(struct sockaddr_storage);
	int data_size;
	if ((data_size = (int)recvfrom(
		     to->file_descriptor, (void *)&(packet->transmit), MTU, 0,
		     (struct sockaddr *)&storage, &storage_size)) == -1) {
		return RECIEVE_FAIL;
	}

	packet->data_size = data_size - sizeof(packet->transmit.header);
	from->file_descriptor = to->file_descriptor;
	from->socket_address = *(struct sockaddr *)&storage;
	from->socket_address_size = __get_sa_len(&from->socket_address);

	if (packet->transmit.header.flags & PACKET_PING) {
		return RECIEVE_PING;
	} else {
		return RECIEVE_DATA;
	}
}
