#include <iostream>

// #include graphics / input

#include "chip8.h"

chip8 myChip8;

int main(int argc, char **argv)
{
    std::cout << "entering main" << std::endl;
    // Set up render system and register input callbacks
    // setupGraphics();
    // setupInput();

    // Initialize the Chip8 system and load the game into the memory
    myChip8.initialise();
    myChip8.loadProgram(std::filesystem::path("chip8_ref/GAMES/PONG"));

    // myChip8.getCurrentState();
    // myChip8.dumpMemory();

    // Emulation loop
    for(;;)
    {
        // Emulate one cycle
        myChip8.emulateCycle();
        // myChip8.getCurrentState();

    //     // If the draw flag is set, update the screen
    //     // if(myChip8.drawFlag)
    //     //     drawGraphics();

    //     // Store key press state (Press and Release)
    //     // myChip8.setKeys();
    }

    std::cout << "returning" << std::endl;
    return 0;
}
