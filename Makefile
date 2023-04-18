CC = cc
SRCS = $(shell find ./src -name "*.c")
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = librsics.so
FLAGS = -O3

all: main

main: $(OBJS)
	$(CC) $(FLAGS)  -shared -fPIC -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm  $(TARGET) $(OBJS)