cmake_minimum_required(VERSION 3.12)
project (RSiCS)


include_directories(src/include)


add_executable(sender src/sender.c)
add_executable(reciever src/reciever.c)