cmake_minimum_required(VERSION 4.2)
project(cpu_sheduling_simulator C)

set(CMAKE_C_STANDARD 11)

add_executable(cpu_sheduling_simulator main.c
        process.h)
