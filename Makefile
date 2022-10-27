reciever: 
	clang reciever.c -o reciever implementation/observe.c implementation/models.c implementation/frame.c

clean:
	rm reciever transmitter
