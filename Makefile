CC = cc
SRCS = $(shell find ./src -name "*.c")
SRCS = $(shell find ./src/include -name "*.h")
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = librsics.so
FLAGS = -O3

all: main

main: $(OBJS)
	$(CC) $(FLAGS)  -shared -fPIC -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

format:
	clang-format -i -style="file:clang-format.txt" src/*.c src/include/*.h

clean: 
	rm  $(TARGET) $(OBJS)
