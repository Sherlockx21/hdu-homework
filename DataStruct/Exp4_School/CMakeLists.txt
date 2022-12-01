cmake_minimum_required(VERSION 3.22)
project(Exp4_School C)

set(CMAKE_C_STANDARD 11)

add_executable(Exp4_School
        map.c map.h visitor.h visitor.c system.c)
