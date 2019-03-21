#include "FieldManagement.hpp"
#include <iostream>
#include <algorithm>

MinesweeperBoard::MinesweeperBoard(int MineQuantity,
                                 int BoardSizeX,
                                 int BoardSizeY) :
                                mineQuantity(MineQuantity),
                                width(BoardSizeX),
                                heigh(BoardSizeY)
{
    if (checkArgsAreNotOutOfRange(MineQuantity, BoardSizeX, BoardSizeY)){
        createBoard();
        setMinesOnRandomFields();
        setNumbersBombNearby();
    }
    else debug::cerr("ERROR! StartBoardMenagement Failed. CheckArgs return false!. ");
}

MinesweeperBoard::MinesweeperBoard(Debug debug,
                                   int MineQuantity,
                                   int BoardSizeX,
                                   int BoardSizeY) :
                                        mineQuantity(MineQuantity),
                                        width(BoardSizeX),
                                        heigh(BoardSizeY)
{
    if (debug == Debug::DEBUG)
        if (checkArgsAreNotOutOfRange(MineQuantity, BoardSizeX, BoardSizeY))
            createBoard();
}

int MinesweeperBoard::getMineCount() const
{
    return mineQuantity;
}

int MinesweeperBoard::getBoardWidth() const
{
    return width;
}

int MinesweeperBoard::getBoardHeight() const
{
    return heigh;
}

bool MinesweeperBoard::checkArgsAreNotOutOfRange(int MineQuantity,
                                     int BoardSizeX,
                                     int BoardSizeY)
{
    if(BoardSizeX <= 1 || BoardSizeY <= 1){
        debug::cerr("ERROR! Wrong Board size given!");
        return false;
    }
    if(MineQuantity == 0){
        debug::cerr("ERROR! Wrong vectorOfBombLocation size!");
        return false;
    }
    if((BoardSizeX-1) * (BoardSizeY-1) < MineQuantity){
        debug::cerr("ERROR! Mine count is same or equal to Board size!");
        return false;
    }
    return true;
}

bool MinesweeperBoard::checkArgsAreNotOutOfRange()
{
    return checkArgsAreNotOutOfRange(getMineCount(), getBoardWidth(), getBoardHeight());
}

bool MinesweeperBoard::checkIsFieldOnBoard(int X, int Y) const
{
    if(getBoardHeight() < Y or getBoardWidth() < X){
        debug::cerr("ERROR! Field location is more than board size, and out of board!");
        return false;
    }
    if(Y < 1 or X < 1){
        debug::cerr("ERROR! Field location is less than 1, and out of board!");
        return false;
    }
    return true;
}

void MinesweeperBoard::createBoard()
{
   for (int ycount = 0; ycount < getBoardHeight(); ycount++){
       if (verticalFields.size() == 0){
           HorizontalFields fakeLane;
           verticalFields.push_back(fakeLane);
       }
       HorizontalFields lane;
       for (int xcount = 0; xcount < getBoardWidth(); xcount++){
           if (lane.horizontalFields.size() == 0){
               Field fakefield;
               lane.horizontalFields.push_back(fakefield);
           }
           Field field;
           lane.horizontalFields.push_back(field);
       }
       lane.horizontalFields.shrink_to_fit();
       verticalFields.push_back(lane);
   }
   verticalFields.shrink_to_fit();
}

void MinesweeperBoard::setMineOnField(int X, int Y)
{
    if (checkIsFieldOnBoard(X ,Y))
        verticalFields.at(Y).horizontalFields.at(X).hasMine = true;
}

void MinesweeperBoard::makeNewBombLocationToVec(int X, int Y)
{
    if (checkIsFieldOnBoard(X ,Y)){
    Vector2xy local(X, Y);
    bombLocation.push_back(local);
    }
}

void MinesweeperBoard::setMinesOnRandomFields()
{
    srand(time(NULL));
    for (int counter = 0; counter < getMineCount(); ++counter){
        int X = rand() % getBoardWidth() + 1;
        int Y = rand() % getBoardHeight() + 1;
        if (!isMineOnField(X, Y))
        {
            setMineOnField(X, Y);
            makeNewBombLocationToVec(X, Y);
        }
        else --counter;
    }
}

void MinesweeperBoard::incrementNumberOfBomb(int X, int Y)
{
    if (checkIsFieldOnBoard(X ,Y))
        ++verticalFields.at(Y).horizontalFields.at(X).numberOfBombNearby;
}

void MinesweeperBoard::setNumbersBombNearby()
{
    /* Is checking place nerby:
     * 1 2 3
     * 4 X 5
     * 6 7 8
     * Is have a bomb.
     */
    for (int countY = 1; countY <= getBoardHeight(); ++countY)
        for (int countX = 1; countX <= getBoardWidth(); ++countX)
                for (int counterY = countY - 1; counterY <= countY + 1; ++counterY)
                    if (counterY > 0 and counterY <= getBoardHeight())
                        for (int counterX = countX - 1; counterX <= countX + 1; ++counterX)
                            if (counterX > 0 and counterX <= getBoardWidth() and
                                    isMineOnField(counterX, counterY) and !isMineOnField(countX, countY))
                                incrementNumberOfBomb(countX, countY);
}

void MinesweeperBoard::setAsNotHiddenFieldsNerbyUpToNumberOnField(int x, int y)
{
    if (!checkIsFieldOnBoard(x, y)) return;
    int X = x;
    int Y = y;
    struct xy {
      int X;
      int Y;
      xy(int x, int y) : X(x), Y(y){}
    };
    std::stack<xy> data;
    do
    {
        if (isHidden(X, Y))
        {
            setNotHidden(X, Y);

            if (!isNOBN(X, Y))
            {
                for (int counterY = Y - 1; counterY <= Y + 1; ++counterY)
                    for (int counterX = X - 1; counterX <= X + 1; ++counterX)
                        if (checkIsFieldOnBoard(counterX, counterY))
                            if (isHidden(counterX, counterY))
                                data.push(xy(counterX, counterY));
            }
        }
            if (!data.empty())
            {
                X = data.top().X;
                Y = data.top().Y;
                data.pop();
            }


    } while (!data.empty());
}

void MinesweeperBoard::showEmptyFieldNearby(int X, int Y)
{
    setAsNotHiddenFieldsNerbyUpToNumberOnField(X, Y);
}

bool MinesweeperBoard::isMineOnField(int X, int Y) const
{
    if (checkIsFieldOnBoard(X ,Y)){
     if (verticalFields.at(Y).horizontalFields.at(X).hasMine == true) return true;
     return false;
    }
}

void MinesweeperBoard::removeFlagFromField(int X, int Y)
{
    if (checkIsFieldOnBoard(X ,Y)){
    if (verticalFields.at(Y).horizontalFields.at(X).userFlag)
        verticalFields.at(Y).horizontalFields.at(X).userFlag = false;
    }
}

void MinesweeperBoard::setFlagOnField(int X, int Y)
{
    if (checkIsFieldOnBoard(X ,Y)){
    if (!verticalFields.at(Y).horizontalFields.at(X).userFlag)
        verticalFields.at(Y).horizontalFields.at(X).userFlag = true;
    }
}

bool MinesweeperBoard::isFlagOnField(int X, int Y) const
{
    if (checkIsFieldOnBoard(X ,Y)){
    if (verticalFields.at(Y).horizontalFields.at(X).userFlag == true) return true;
    return false;
    }
}

bool MinesweeperBoard::isHidden(int X, int Y) const
{
    if (checkIsFieldOnBoard(X ,Y)){
    if (verticalFields.at(Y).horizontalFields.at(X).isHidden == true) return true;
    return false;
    }
}

void MinesweeperBoard::setNotHidden(int X, int Y)
{
    if (checkIsFieldOnBoard(X ,Y)){
    if (verticalFields.at(Y).horizontalFields.at(X).isHidden)
        verticalFields.at(Y).horizontalFields.at(X).isHidden = false;
    }
}

bool MinesweeperBoard::isNOBN (int X, int Y) const
{
    if (checkIsFieldOnBoard(X, Y)){
        if (verticalFields.at(Y).horizontalFields.at(X).numberOfBombNearby > 0) return true;
        else return false;
    }
}
int MinesweeperBoard::getNOBN (int X, int Y) const
{
    if (checkIsFieldOnBoard(X, Y))
    return verticalFields.at(Y).horizontalFields.at(X).numberOfBombNearby;
}

std::vector<Vector2xy> MinesweeperBoard::getMinesLocation() const
{
    return bombLocation;
}
/*
void MinesweeperBoard::debug_display() const
{
        std::cout << "Bombs: " << std::endl;
        std::cout << " ";
        for (int counter = 1; counter <= getBoardWidth(); ++counter) std::cout << " " << counter;
        std::cout << std::endl;
        for (int sY = 1; sY <= getBoardHeight(); ++sY)
        {
            std::cout << sY;
            for (int sX = 1; sX <= getBoardWidth(); ++sX)
            {
               std::cout << " " << isMineOnField(sX, sY);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "NOBN: " << std::endl;
        std::cout << " ";
        for (int counter = 1; counter <= getBoardWidth(); ++counter) std::cout << " " << counter;
        std::cout << std::endl;
        for (int sY = 1; sY <= getBoardHeight(); ++sY)
        {
            std::cout << sY;
            for (int sX = 1; sX <= getBoardWidth(); ++sX)
            {
               std::cout << " " << getNOBN(sX, sY);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
}
*/
