cmake_minimum_required(VERSION 3.22)
project(Exp2_Language C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Exp2_Language
        queue.h queue.c stack.h stack.c check.h check.c parse.h parse.c Translator.c)
