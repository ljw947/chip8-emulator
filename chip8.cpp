#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>

#include <unistd.h>  // for sleep

#include "chip8.h"

typedef unsigned char byte;

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

    // clear keys
    for (int i = 0; i < 16; ++i) { key[i] = 0x00; }

    // load fontset
    unsigned char buffer = 0x50;
    for (int i = 0; i < 80; ++i) {
        memory[buffer + i] = chip8_fontset[i];
    }

    // reset timers
    delayTimer = 0;
    soundTimer = 0;

    // so I don't go crazy
    cycleCount = 0;
}

void chip8::loadProgram(std::filesystem::path pathName) {
    std::cout << "loading program" << std::endl;

    if (!std::filesystem::exists(pathName)) {
        std::cout << "file doesn't exist" << std::endl;
        return;
    }

    std::ifstream file(pathName, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return;
    }

    std::vector<byte> buffer(
        (std::istreambuf_iterator<char>(file)),
         std::istreambuf_iterator<char>()
    );

    int romStartAddress = 512;
    for (int i = 0; i < buffer.size(); ++i) {
        memory[romStartAddress + i] = buffer[i];
    }

    std::cout << "loaded program" << std::endl;
}

void chip8::emulateCycle() {
    std::cout << "emulating cycle " << cycleCount << std::endl;

    // fetch opcode
    opcode = memory[pc] << 8 | memory[pc + 1];

    // decode, execute opcode by looking at first 4 bits
    switch(opcode & 0xF000) {
        // first 4 bits aren't clear enough in this instance
        case 0x0000:
            switch(opcode & 0x000F) {
                // 0x00E0: clear screen
                case 0x0000:
                    break;
                // 0x000EE: return from subroutine
                case 0x000E:
                    break;
                default:
                    printf("Unknown opcode: 0x%X\n", opcode);
            }

        // ANNN: set I to address NNN
        case 0xA000:
            printf("Got opcode: 0x%X\n", opcode);
            I = opcode & 0x0FFF;
            pc += 2;
            break;

        // more opcodes

        default:
            printf("Unknown opcode: 0x%X\n", opcode);
    }

    // update timers
    if (delayTimer > 0) { --delayTimer; }
    if (soundTimer > 0) {
        if (soundTimer == 1) { std::cout << "beep" << std::endl; }
        --soundTimer;
    }

    sleep(1);
    ++cycleCount;
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

void chip8::dumpMemory(int startByte = 0, int stopByte = 4096) {
    std::cout << "memory: " << std::endl;
    for (int i = startByte; i < stopByte; ++i) {
        printf("%.4X : ", i);
        printf("%.4X\n", memory[i]);
    }
}
