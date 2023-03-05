#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>

#include <vector>

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

    std::istream_iterator<unsigned char> begin(file), end;
    std::vector<unsigned char> buffer(begin, end);

    std::ofstream myFile("data.bin", std::ios::out | std::ios::binary);
    
    int romStartAddress = 512;
    for (int i : buffer) {
        memory[romStartAddress + i] = buffer[i];
        // delete
        char ch = (char)buffer[i];
        myFile.write(&ch,1);
    }

    // std::copy(
    //     buffer.begin(),
    //     buffer.end(),
    //     std::ostream_iterator<unsigned char>(std::cout, ",")
    // );

    // std::vector<unsigned char> blocks;
    // std::cout << sizeof(blocks);
    // std::cout << "file contents are in memory" << std::endl;
    // for(int i = 0; i < sizeof(blocks); ++i) {
    //     // printf("%.16X\n", blocks[i]);
    //     std::cout << std::hex <<  blocks[i];
    // }

    std::cout << "loaded program" << std::endl;
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
    for (int i = 0; i < 1024; ++i) {
        printf("%.4X : ", i);
        printf("%.4X\n", memory[i]);
    }
}
