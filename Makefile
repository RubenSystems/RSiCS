CC = gcc
SRCS = $(shell find ./src -name "*.c")
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = librsics.so
FLAGS = -O3 -shared

all: main

main: $(OBJS)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm  $(TARGET) $(OBJS)