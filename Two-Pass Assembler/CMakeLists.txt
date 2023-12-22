cmake_minimum_required(VERSION 3.26)
project(twoPass C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(project3
        directives.c
        directives.h
        errors.c
        errors.h
        headers.h
        main.c
        opcodes.c
        opcodes.h
        symbols.c
        symbols.h)
