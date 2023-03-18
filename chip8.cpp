#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>

#include <unistd.h>  // for sleep

#include "chip8.h"

typedef unsigned char byte;

void chip8::initialise()
{
    std::cout << "initialising" << std::endl;
    pc = 0x200;  // prior bytes reserved
    opcode = 0;
    I = 0;
    sp = 0;

    // clear display call
    drawFlag = false;

    // clear stack
    for (int i = 0; i < 16; ++i) { stack[i] = 0x00; }

    // clear registers
    for (int i = 0; i < 16; ++i) { V[i] = 0x00; }

    // clear memory
    for (int i = 0; i < 4096; ++i) { memory[i] = 0x00; }

    // clear keys
    for (int i = 0; i < 16; ++i) { key[i] = 0x00; }

    // load fontset
    unsigned char buffer = 0x50;
    for (int i = 0; i < 80; ++i)
    {
        memory[buffer + i] = chip8_fontset[i];
    }

    // reset timers
    delayTimer = 0;
    soundTimer = 0;

    // so I don't go crazy
    cycleCount = 0;
}

void chip8::loadProgram(std::filesystem::path pathName)
{
    std::cout << "loading program" << std::endl;

    if (!std::filesystem::exists(pathName))
    {
        std::cout << "file doesn't exist" << std::endl;
        return;
    }

    std::ifstream file(pathName, std::ios::binary);

    if (!file.is_open())
    {
        std::cout << "Unable to open file" << std::endl;
        return;
    }

    std::vector<byte> buffer(
        (std::istreambuf_iterator<char>(file)),
         std::istreambuf_iterator<char>()
    );

    int romStartAddress = 512;
    for (int i = 0; i < buffer.size(); ++i)
    {
        memory[romStartAddress + i] = buffer[i];
    }

    std::cout << "loaded program" << std::endl;
}

void chip8::emulateCycle()
{
    std::cout << "emulating cycle " << cycleCount << std::endl;

    // fetch opcode
    opcode = memory[pc] << 8 | memory[pc + 1];
    printf("Got opcode: 0x%X\n", opcode);

    // decode, execute opcode by looking at first 4 bits (e.g. the X in 0xX)
    switch(opcode & 0xF000)
    {
        // first 4 bits aren't clear enough in this instance
        case 0x0000:
            switch(opcode & 0x000F)
            {
                // 0x00E0: clear screen
                case 0x0000:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                // 0x00EE: return from subroutine
                case 0x000E:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                default:
                    printf("Unknown opcode: 0x%X\n", opcode);
            }

        // 1NNN: go to address NNN
        case 0x1000:
        {
            printf("Not yet implemented: 0x%X\n", opcode);
            pc += 2;  // TODO: check if needed
            break;
        }

        // 2NNN: run subroutine at NNN
        case 0x2000:
        {
            printf("Not yet implemented: 0x%X\n", opcode);
            pc += 2;  // TODO: check if needed
            break;
        }

        // 3XNN: skip next instruction if VX == NN
        case 0x3000:
        {
            printf("Not yet implemented: 0x%X\n", opcode);
            pc += 2;  // TODO: check if needed
            break;
        }

        // 4XNN: skip next instruction if VX != NN
        case 0x4000:
        {
            printf("Not yet implemented: 0x%X\n", opcode);
            pc += 2;  // TODO: check if needed
            break;
        }

        // 5XY0: skip next instruction if VX == VY
        case 0x5000:
        {
            printf("Not yet implemented: 0x%X\n", opcode);
            pc += 2;  // TODO: check if needed
            break;
        }

        // 6XNN: set VX to NN
        case 0x6000:
        {
            V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
            pc += 2;
            break;
        }

        // 7XNN: add NN to VX (carry flag unchanged)
        case 0x7000:
        {
            printf("Not yet implemented: 0x%X\n", opcode);
            pc += 2;  // TODO: check if needed
            break;
        }

        case 0x8000:
        {
            switch(opcode & 0x000F)
            {
                // 8XY0: set VX to value of VY
                case 0x0000:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                // 8XY1: set VX to VX OR VY (bitwise OR)
                case 0x0001:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                // 8XY2: set VX to VX AND VY (bitwise AND)
                case 0x0002:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                // 8XY3: set VX to VX XOR VY (bitwise XOR)
                case 0x0003:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                // 8XY4: add VY to VX. VF set to 1 when carrying, otherwise 0
                case 0x0004:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                // 8XY5: subtract VY from VX. VF set to 0 when borrowing, otherwise 0
                case 0x0005:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                // 8XY6: store least-significant bit of VX in VF, then shift VX right by 1
                case 0x0006:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                // 8XY7: set VX to VY minus VX. VF set to 0 when there is a borrow, otherwise 1
                case 0x0007:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                // 8XYE: store most-significant bit of VX in VF, then shift VX left by 1
                case 0x000E:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                default:
                    printf("Unknown opcode: 0x%X\n", opcode);
            }
        }

        // 9XY0: skip next instruction if VX != VY
        case 0x9000:
        {
            printf("Not yet implemented: 0x%X\n", opcode);
            pc += 2;  // TODO: check if needed
            break;
        }

        // ANNN: set I to address NNN
        case 0xA000:
        {
            I = opcode & 0x0FFF;
            pc += 2;
            break;
        }

        // BNNN: jump to address NNN plus V0
        case 0xB000:
        {
            printf("Not yet implemented: 0x%X\n", opcode);
            pc += 2;  // TODO: check if needed
            break;
        }

        // CXNN: set VX to result of bitwise AND operation on random number (0 - 255) and NN
        case 0xC000:
        {
            printf("Not yet implemented: 0x%X\n", opcode);
            pc += 2;  // TODO: check if needed
            break;
        }

        // DXYN: Draw sprite at Vx, Vy with width 8 pixels, height N pixels.
        // Pixel set using bitwise XOR - current state compared w/ value in memory, if different 1 else 0
        case 0xD000:
        {
            unsigned short x = V[(opcode & 0x0F00) >> 8];
            unsigned short y = V[(opcode & 0x00F0) >> 4];
            unsigned short height = opcode & 0x000F;
            unsigned short pixel;

            V[0xF] = 0;  // reset VF
            for (int yline = 0; yline < height; ++yline)
            {
                pixel = memory[I + yline];
                for (int xline = 0; xline < 8; ++xline)
                {
                    if ((pixel & (0x80 >> xline)) != 0)
                    {
                        if (gfx[(x + xline + ((y + yline) * 64))] == 1) { V[0xF] = 1; }
                        gfx[x + xline + ((y + yline) * 64)] ^= 1;
                    }
                }
            }
            drawFlag = true;
            pc += 2;
            break;
        }

        case 0xE000:
        {
            switch(opcode & 0x000F)
            {
                // EX9E: skip next instruction if key stored in VX is pressed
                case 0x000E:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }
                // EXA1: skip next instruction if key stored in VX is not pressed
                case 0x0001:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                default:
                    printf("Unknown opcode: 0x%X\n", opcode);
            }
        }

        case 0xF000:
        {
            switch(opcode & 0x00FF)
            {
                // FX07: set VX to value of delay timer
                case 0x0007:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                // FX0A: wait for keypress then store in VX (blocking operation)
                case 0x000A:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                // FX15: set delay timer to VX
                case 0x0015:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                // FX18: set sound timer to VX
                case 0x0018:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                // FX1E: add VX to I. VF is unaffected
                case 0x001E:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                // FX29: set I to location of sprite for character in VX. Chars 0 - F represented by 4x5 font
                case 0x0029:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                // FX33: Store binary-coded decimal representation of VX:
                //       with hundreds digit at I,
                //       tens digit at I+1,
                //       ones digit at I+2
                case 0x0033:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                // FX55: Store V0 to VX (incl. VX) in memory starting at address I.
                //       Offset from I increased by 1 each time, I left unchanged
                case 0x0055:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                // FX65: Fill V0 to VX (incl. VX) with values from memory starting at address I.
                //       Offset from I increased by 1 each time, I left unchanged
                case 0x0065:
                {
                    printf("Not yet implemented: 0x%X\n", opcode);
                    pc += 2;  // TODO: check if needed
                    break;
                }

                default:
                    printf("Unknown opcode: 0x%X\n", opcode);
            }
        }

        default:
            printf("Unknown opcode: 0x%X\n", opcode);
    }

    // update timers
    if (delayTimer > 0) { --delayTimer; }
    if (soundTimer > 0)
    {
        if (soundTimer == 1) { std::cout << "beep" << std::endl; }
        --soundTimer;
    }

    ++cycleCount;
}

unsigned char* chip8::getGfx() { return gfx; }

void chip8::getCurrentState()
{
    printf("opcode: 0x%X\n", opcode);
    std::cout << "I: " << I << std::endl;
    std::cout << "pc: " << pc << std::endl;
    std::cout << "delayTimer: " << delayTimer << std::endl;
    std::cout << "soundTimer: " << soundTimer << std::endl;
    std::cout << "sp: " << sp << std::endl;

    std::cout << "registers:" << std::endl;
    for (int i = 0; i < 16; ++i)
    {
        printf("register %i: %i\n", i, V[i]);
    }

    for (int i = 0; i < 16; ++i) { std::cout << "stack: " << stack[i] << std::endl; }
}

void chip8::dumpMemory(int startByte = 0, int stopByte = 4096)
{
    std::cout << "memory: " << std::endl;
    for (int i = startByte; i < stopByte; ++i) {
        printf("%.4X : ", i);
        printf("%.4X\n", memory[i]);
    }
}
