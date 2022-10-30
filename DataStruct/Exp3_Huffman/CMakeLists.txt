cmake_minimum_required(VERSION 3.22)
project(Exp3_Huffman C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Exp3_Huffman
        decoding.c
        decoding.h
        encoding.c
        encoding.h
        initialize.c
        initialize.h
        textprint.c
        textprint.h
        treeprint.c
        treeprint.h main.c)
