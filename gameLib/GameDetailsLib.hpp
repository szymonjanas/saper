#pragma once
#include "Operations.hpp"

class GameDetails
{
    int sizeX;
    int sizeY;
    int bombQuantity;

public:
    GameDetails(Level level)
    {
        switch (level)
        {
        case Level::EASY:
            sizeX = 8;
            sizeY = 8;
            bombQuantity = 10;
            break;
        case Level::MEDIUM:
            sizeX = 16;
            sizeY = 16;
            bombQuantity = 40;
            break;
        case Level::HARD:
            sizeX = 30;
            sizeY = 16;
            bombQuantity = 99;
            break;
        }
    }
    GameDetails(Level level,
                int SizeX,
                int SizeY,
                int BombQuantity)
    {
        if (level == Level::USER)
        {
            sizeX = SizeX;
            sizeY = SizeY;
            bombQuantity = BombQuantity;
        }
    }
    int getSizeX() const { return sizeX; }
    int getSizeY() const { return sizeY; }
    int getBombQuantity() const {return bombQuantity; }
};

struct MinMaxFieldSizeAndBombQuantity
{
    const int MaxTableSizeX;
    const int MaxTableSizeY;
    const int MinTableSizeX;
    const int MinTableSizeY;
    const int MaxBombQuantity;
    const int MinBombQuantity;

    MinMaxFieldSizeAndBombQuantity() : MaxTableSizeX(30),
                                       MinTableSizeX(8),
                                       MaxTableSizeY(24),
                                       MinTableSizeY(8),
                                       MaxBombQuantity(668),
                                       MinBombQuantity(10) {}


};
