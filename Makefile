reciever: 
	gcc -O3 -shared -o rsics_build.so src/observe.c src/models.c src/frame.c

clean:
	rm rsics_build.so 
