#pragma once
#include "Operations.hpp"

class GameDetails
{
    int sizeX;
    int sizeY;
    int MineQuantity;

public:
    GameDetails(Level level)
    {
        switch (level)
        {
        case Level::EASY:
            sizeX = 8;
            sizeY = 8;
            MineQuantity = 10;
            break;
        case Level::MEDIUM:
            sizeX = 16;
            sizeY = 16;
            MineQuantity = 40;
            break;
        case Level::HARD:
            sizeX = 30;
            sizeY = 16;
            MineQuantity = 99;
            break;
        case Level::USER:
            break;
        }
    }
    GameDetails(Level level,
                int SizeX,
                int SizeY,
                int MineQuantity)
    {
        if (level == Level::USER)
        {
            sizeX = SizeX;
            sizeY = SizeY;
            this->MineQuantity = MineQuantity;
        }
    }
    int getSizeX() const { return sizeX; }
    int getSizeY() const { return sizeY; }
    int getMineQuantity() const {return MineQuantity; }
};

struct MinMaxFieldSizeAndMineQuantity
{
    const int MaxBoardSizeX;
    const int MinBoardSizeX;
    const int MaxBoardSizeY;
    const int MinBoardSizeY;
    const int MaxMineQuantity;
    const int MinMineQuantity;

    MinMaxFieldSizeAndMineQuantity() : MaxBoardSizeX(30),
                                       MinBoardSizeX(8),
                                       MaxBoardSizeY(24),
                                       MinBoardSizeY(8),
                                       MaxMineQuantity(668),
                                       MinMineQuantity(10) {}


};
