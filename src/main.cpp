#include <cstring>
#include <iostream>

#include <unistd.h>  // for sleep

// #include graphics / input

#include "chip8.h"
#include "graphics.h"

chip8 myChip8;

std::string filePath;

void showHelpAndExit()
{
    std::cout << "chip8 emulator" << std::endl;
    std::cout << "-p / --path      path to file" << std::endl;
    std::cout << "-h / --help      show this help message" << std::endl;
    exit(0);
}

void parseArgs(int argc, char* argv[])
{
    if (argc < 2) { showHelpAndExit(); }

    for (int i = 0; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "--help") | std::strcmp(argv[i], "--h")) { showHelpAndExit(); }
        if (std::strcmp(argv[i], "--path") | std::strcmp(argv[i], "--p")) { filePath = argv[i + 1]; }
    }
}

int main(int argc, char* argv[])
{
    // Set up render system and register input callbacks
    // setupGraphics();
    // setupInput();

    parseArgs(argc, argv);

    // Initialize the Chip8 system and load the game into the memory
    myChip8.initialise();
    bool programLoaded = myChip8.loadProgram(std::filesystem::path(filePath));

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
