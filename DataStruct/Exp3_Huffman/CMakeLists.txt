cmake_minimum_required(VERSION 3.22)
project(Exp3_Huffman C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Exp3_Huffman
        union_H.h
        huffman.c
        huffman.h
        text.c
        text.h
        stack.c
        stack.h  main.c)
