reciever: 
	clang -O3 reciever.c -o reciever implementation/observe.c implementation/models.c implementation/frame.c

clean:
	rm reciever transmitter