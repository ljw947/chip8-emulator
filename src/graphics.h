#pragma once

#include <iostream>

void drawHorizontalBorder()
{
    std::string horizontalLine = "\u2501";
    std::string heavyCross = "\u254B";
    std::string horizontalBorder;
    horizontalBorder.append(heavyCross);
    for (int x = 0; x < 66; ++x)  // for padding
    {
        horizontalBorder.append(horizontalLine);
    }
    horizontalBorder.append(heavyCross);
    std::cout << horizontalBorder << std::endl;
}

void printScreen(unsigned char gfx[64 * 32])
{
    int counter = 0;
    std::string line;
    std::string block = "\u2588";
    std::string space = "\u0020";
    std::string verticalLine = "\u2503";
    std::cout << std::endl;
    drawHorizontalBorder();
    for (int x = 0; x < (64 * 32); ++x)
    {
        if (gfx[x] == 0x01)
            line.append(block);
        else
            line.append(space);

        if (counter == 63)  // for x = 64
        {
            std::cout << verticalLine << space << line << space << verticalLine << std::endl;
            line.clear();
            counter = 0;
        }
        else { ++counter; }
    }
    drawHorizontalBorder();
    std::cout << std::endl;
}

