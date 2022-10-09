reciever: implementation/transmit.c implementation/observe.c implementation/models.c
	clang $(CFLAGS) reciever.c $? -o bin/reciever  
