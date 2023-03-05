#include <iostream>

#include "chip8.h"

// initialise registers and memory once
void chip8::initialise() {
    std::cout << "initialising" << std::endl;
    pc = 0x200;  // prior bytes reserved
    opcode = 0;
    I = 0;
    sp = 0;

    // clear display call

    // clear stack
    for (int i = 0; i < 16; ++i) { stack[i] = 0x00; }

    // clear registers
    for (int i = 0; i < 16; ++i) { registers[i] = 0x00; }

    // clear memory
    for (int i = 0; i < 4096; ++i) { memory[i] = 0x00; }

    // load fontset
    for (int i = 0; i < 80; ++i) {
        unsigned char buffer = 0x50;
        memory[buffer + i] = chip8_fontset[i];
    }

    // reset timers
    delayTimer = 0;
    soundTimer = 0;
}

void chip8::loadProgram(std::string pathName) {
    std::cout << pathName << std::endl;
}

void chip8::emulateCycle() {
    std::cout << "emulating cycle" << std::endl;
    // fetch opcode
    // decode opcode
    // execute opcode

    // update timers
}

void chip8::getCurrentState() {
    std::cout << "opcode: " << opcode << std::endl;
    std::cout << "I: " << I << std::endl;
    std::cout << "pc: " << pc << std::endl;
    std::cout << "gfx: " << gfx << std::endl;
    std::cout << "delayTimer: " << delayTimer << std::endl;
    std::cout << "soundTimer: " << soundTimer << std::endl;
    std::cout << "sp: " << sp << std::endl;

    for (int i = 0; i < 16; ++i) { std::cout << "registers: " << registers[i] << std::endl; }

    for (int i = 0; i < 16; ++i) { std::cout << "stack: " << stack[i] << std::endl; }
}

void chip8::dumpMemory() {
    std::cout << "memory: " << std::endl;
    for (int i = 0; i < 4096; ++i) {
        printf("%.4X : ", i);
        printf("%.4X\n", memory[i]);
    }
}
