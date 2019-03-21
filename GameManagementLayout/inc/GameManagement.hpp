#pragma once

#include "FieldManagement.hpp"
#include "Operations.hpp"
#include "MessegesDebug.hpp"

#include <vector>



class GameManagement
{
    /*  Available mode:
     *  easy
     *  medium
     *  hard
     *  user
    */
    MinesweeperBoard* game;

    int flagsNumber = 0;
    bool incrementFlagsNumber();
    bool decrementFlagsNumber();
    Vector2xy blowUp;

public:

    GameManagement(Level level);
    GameManagement(Level level,
                   int BoardSizeX,
                   int BoardSizeY,
                   int MineQuantity);
    GameManagement(MinesweeperBoard& board);
    ~GameManagement();

    bool checkIsSizeAndMineQuantityInRange( int &BoardSizeX,
                                            int &BoardSizeY,
                                            int &MineQuantity);

    int scores();

    bool isFlag(int X, int Y) const;
    void makeFlag(int X, int Y);
    void removeFlag(int X, int Y);
    FieldStatus getFieldSign(int X, int Y);
    bool checkAndSetField(int X, int Y);

    int getSizeX() const;
    int getSizeY() const;
    int getMineQuantity() const;
    int getNOBN(int X, int Y) const;

    void setAllFieldsNotHidden();

    bool isFieldOnTheBoard(int X, int Y);

    GameStatus checkGameStatus();
    Vector2xy getBlowUp() const;

    void debug_display(MinesweeperBoard* board);
};
