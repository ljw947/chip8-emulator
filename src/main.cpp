#include <iostream>

#include <unistd.h>  // for sleep

// #include graphics / input

#include "chip8.h"
#include "graphics.h"

chip8 myChip8;

int main(int argc, char **argv)
{
    // Set up render system and register input callbacks
    // setupGraphics();
    // setupInput();

    // Initialize the Chip8 system and load the game into the memory
    myChip8.initialise();
    bool programLoaded = myChip8.loadProgram(std::filesystem::path("chip8_ref/GAMES/PONG"));

    if (!programLoaded)
    {
        std::cout << "Unable to load program, exiting." << std::endl;
        exit(1);
    }

    // myChip8.getCurrentState();
    // myChip8.dumpMemory();

    // Emulation loop
    for(;;)
    {
        // Emulate one cycle
        myChip8.emulateCycle();

        // only draw when needed
        if (myChip8.drawFlag)
        {
            printScreen(myChip8.getGfx());
            myChip8.drawFlag = false;
        }

        // Store key press state (Press and Release)
        // myChip8.setKeys();

        sleep(1);
    }

    return 0;
}
