#pragma once

#include <filesystem>
#include <vector>

class chip8 {
private:
    int cycleCount;
    // opcodes are 2 bytes, big-endian (MSB)
    unsigned short opcode;

    // 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
    // 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
    // 0x200-0xFFF - Program ROM and work RAM
    unsigned char memory[4096];

    // 8-bit data registers, V0 to VF
    //
    // VF:
    // - avoid, it's a flag for some instructions
    // - the carry flag in addition
    // - the no borrow flag in subtraction
    // - set upon pixel collision during draw
    unsigned char V[16];

    unsigned short I;  // address register, 12 bits
    unsigned short pc;  // program counter

    // 2048 pixels total, either on (1) or off (0)
    unsigned char gfx[64 * 32];

    // timers, both count down at 60Hz to 0
    unsigned char delayTimer;  // value can be set or read
    unsigned char soundTimer;  // when non-zero, triggers onboard buzzer

    // store return addresses when subroutines are called
    // used to remember the current location before a jump is performed
    // store the program counter in the stack before proceeding
    // The system has 16 levels of stack, `sp` remembers which level of the stack is used
    unsigned short stack[16];
    unsigned short sp;

    // current state of keys
    unsigned char key[16];

    int programSize;

public:
    // initialise all registers and memory locations
    void initialise();
    // load contents of pathName into memory
    bool loadProgram(std::filesystem::path pathName);
    // fetch, decode, execute opcode; update timers
    void emulateCycle();
    // get current state of key presses
    void setKeys();

    // dumps values of all private member variables except memory
    void getCurrentState();
    // dumps contents of memory
    void dumpMemory(int startByte, int stopByte);
    // dumps contents of memory to a file
    void dumpMemoryToFile(int startByte, int stopByte);
    // print contents of gfx (rudimentary print screen)
    void printScreen();
    // clears gfx array
    void clearGfx();

    // return the gfx array for drawing
    unsigned char* getGfx();

    bool drawFlag;

    // the 'official' fontset of chip8
    unsigned char chip8_fontset[80] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
};
