#pragma once

#include<vector>
#include<iostream>
#include <stack>

struct Field
{
    Field(){
        hasMine = false;
        userFlag = false;
        isHidden = true;
        numberOfBombNearby = 0;
        visitedDFS = false;
    }
    bool visitedDFS; //for Depth First Search
    bool hasMine;
    bool userFlag;
    bool isHidden;
    int numberOfBombNearby;
};

struct HorizontalFields
{
    std::vector<Field> horizontalFields;
};

struct Location
{
  int x;
  int y;
  Location(){;}
  Location(int X, int Y) :
      x(X), y(Y) {}
};

class MinesweeperBoard
{
    void error(std::string err);

    std::vector<HorizontalFields> verticalFields;

    const int mineQuantity;
    const int width;
    const int heigh;

    void setBoardSizeX(int X);
    void setBoardSizeY(int Y);

    void createBoard();

    void setMineQuantity(int MineQuantity);
    void setMineOnField(int X, int Y);
    void setMinesOnRandomFields();

    void incrementNumberOfBomb(int X, int Y);
    void setNumbersBombNearby();

    std::stack<Location> stackDFS;
    void setVisitedDFS(int X, int Y);
    bool isVisited(int X, int Y) const;
    void setAsNotHiddenFieldsNerbyUpToNumberOnField(int X, int Y);

    std::vector<Location> bombLocation;
    void makeNewBombLocationToVec(int X, int Y);

 public:

    MinesweeperBoard(int MineQuantity,
                    int BoardSizeX,
                    int BoardSizeY);

    bool checkArgsAreNotOutOfRange() const;
    bool checkArgsAreNotOutOfRange(  int MineQuantity,
                                int BoardSizeX,
                                int BoardSizeY) const;

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

    void startBoardMenagement(int MineQuantity,
                              int BoardSizeX,
                              int BoardSizeY);

    std::vector<Location> getMinesLocation() const;

    int getMineCount() const;
    int getBoardWidth() const;
    int getBoardHeight() const;

    void debug_display() const;

};
