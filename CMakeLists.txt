cmake_minimum_required(VERSION 3.20)
project(CSA_Homework_5)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $"{BUILD_DIR}/../bin")
set(SOURCE_FILES
        people.h
        barbershop.h

        barbershop.cpp
        people.cpp
        main.cpp)

add_executable(CSA_Homework_5 ${SOURCE_FILES})
