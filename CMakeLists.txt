cmake_minimum_required(VERSION 3.24)
project(Protocol)

set(CMAKE_CXX_STANDARD 11)

add_executable(Protocol Source/main.c Source/pack.c Source/pack.c Source/protocol.c Source/unpack.c Header/pack.h Header/protocol.h Header/unpack.h Header/receive.h Source/receive.c Header/public.h)
