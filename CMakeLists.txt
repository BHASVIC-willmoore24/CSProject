cmake_minimum_required(VERSION 3.28)
project(CSProject C)

set(CMAKE_C_STANDARD 11)

add_executable(CSProject main.c
        check_out.c
        check_in.c
        booking_dinner.c)
