#pragma once

#include<vector>
#include<iostream>
#include <stack>
#include "MessegesDebug.hpp"
#include "Operations.hpp"

struct Field
{
    Field(){
        hasMine = false;
        userFlag = false;
        isHidden = true;
        numberOfBombNearby = 0;
    }
    bool hasMine;
    bool userFlag;
    bool isHidden;
    int numberOfBombNearby;
};

struct HorizontalFields
{
    std::vector<Field> horizontalFields;
};

struct Vector2xy
{
  int x;
  int y;
  Vector2xy(){;}
  Vector2xy(int X, int Y) :
      x(X), y(Y) {}
};

class MinesweeperBoard
{
    std::vector<HorizontalFields> verticalFields;

    const int mineQuantity;
    const int width;
    const int heigh;

    void createBoard();

    void setMineOnField(int X, int Y);
    void setMinesOnRandomFields();

    void incrementNumberOfBomb(int X, int Y);
    void setNumbersBombNearby();

    void setAsNotHiddenFieldsNerbyUpToNumberOnField(int X, int Y);

    std::vector<Vector2xy> bombLocation;
    void makeNewBombLocationToVec(int X, int Y);

 public:

    MinesweeperBoard(int MineQuantity,
                    int BoardSizeX,
                    int BoardSizeY);
    MinesweeperBoard(Debug debug,
                     int MineQuantity,
                     int BoardSizeX,
                     int BoardSizeY);
    bool checkArgsAreNotOutOfRange();
    bool checkArgsAreNotOutOfRange( int MineQuantity,
                                    int BoardSizeX,
                                    int BoardSizeY);

    bool checkIsFieldOnBoard(int X, int Y) const;

    //NOBN - Numbers of Bomb Nerby
    bool isNOBN  (int X, int Y) const;
    int getNOBN  (int X, int Y) const;

    bool isFlagOnField  (int X, int Y) const;
    void setFlagOnField (int X, int Y);
    void removeFlagFromField(int X, int Y);

    bool isHidden       (int X, int Y) const;
    void setNotHidden   (int X, int Y);

    bool isMineOnField  (int X, int Y) const;

    void showEmptyFieldNearby(int X, int Y);

    std::vector<Vector2xy> getMinesLocation() const;

    int getMineCount() const;
    int getBoardWidth() const;
    int getBoardHeight() const;

    //void debug_display() const;
};
