cmake_minimum_required(VERSION 3.22)

project(chip8-emulator)

add_executable(
    chip8-emulator

    src/main.cpp
    src/chip8.cpp
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
