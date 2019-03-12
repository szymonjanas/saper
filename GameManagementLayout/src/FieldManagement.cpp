#include "FieldManagement.hpp"
#include <iostream>
#include <algorithm>

void MinesweeperBoard::error(std::string err)
{
    std::cerr << "ERROR! " << err << std::endl;
}

MinesweeperBoard::MinesweeperBoard(int MineQuantity,
                                 int BoardSizeX,
                                 int BoardSizeY) :
                                mineQuantity(MineQuantity),
                                width(BoardSizeX),
                                heigh(BoardSizeY) {}

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
                                     int BoardSizeY) const
{
    if(BoardSizeX <= 1 || BoardSizeY <= 1){
        error("ERROR! Wrong Board size given!");
        return false;
    }
    if(MineQuantity == 0){
        error("ERROR! Wrong vectorOfBombLocation size!");
        return false;
    }
    if((BoardSizeX-1) * (BoardSizeY-1) < MineQuantity){
        error("ERROR! Mine count is same or equal to Board size!");
        return false;
    }
    return true;
}

bool MinesweeperBoard::checkArgsAreNotOutOfRange() const
{
    return checkArgsAreNotOutOfRange(getMineCount(), getBoardWidth(), getBoardHeight());
}

bool MinesweeperBoard::checkIsFieldOnBoard(int X, int Y) const
{
    if(getBoardHeight() < Y or getBoardWidth() < X){
        error("ERROR! Field location is more than board size, and out of board!");
        return false;
    }
    if(Y < 1 or X < 1){
        error("ERROR! Field location is less than 1, and out of board!");
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
    Location local(X, Y);
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

void MinesweeperBoard::setVisitedDFS(int X, int Y)
{
    if (checkIsFieldOnBoard(X ,Y)){
    verticalFields.at(Y).horizontalFields.at(X).visitedDFS = true;
    }
}

bool MinesweeperBoard::isVisited(int X, int Y) const
{
    if (checkIsFieldOnBoard(X ,Y)){
    if(verticalFields.at(Y).horizontalFields.at(X).visitedDFS) return true;
    else return false;
    }
}

void MinesweeperBoard::setAsNotHiddenFieldsNerbyUpToNumberOnField(int X, int Y)
{
    if (checkIsFieldOnBoard(X ,Y)){
    if (!isVisited(X, Y))
    {
        do{
            if (!stackDFS.empty()) stackDFS.pop();
            setVisitedDFS(X, Y);
            setNotHidden(X, Y);
            if (isNOBN(X, Y)) {return;}
            else
            {
                for (int counterY = Y - 1; counterY <= Y + 1; ++counterY)
                    if (counterY > 0 and counterY <= getBoardHeight())
                        for (int counterX = X - 1; counterX <= X + 1; ++counterX)
                            if (    counterX > 0 and
                                    counterX <= getBoardWidth() and
                                    !isVisited(counterX , counterY))
                            {
                                Location local(counterX, counterY);
                                stackDFS.push(local);
                            }
            }
            if (!stackDFS.empty())
                setAsNotHiddenFieldsNerbyUpToNumberOnField(stackDFS.top().x, stackDFS.top().y);

        } while(!stackDFS.empty());
    }
    }
    return;
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

void MinesweeperBoard::setBoardSizeX(int Width)
{
    width = Width;
}

void MinesweeperBoard::setBoardSizeY(int Heigh)
{
    heigh = Heigh;
}

void MinesweeperBoard::setMineQuantity(int MineQuantity)
{
    mineQuantity = MineQuantity;
}

void MinesweeperBoard::startBoardMenagement(int MineQuantity,
                                           int BoardSizeX,
                                           int BoardSizeY)
{
    if (checkArgsAreNotOutOfRange(MineQuantity, BoardSizeX, BoardSizeY)){
        setMineQuantity(MineQuantity);
        setBoardSizeX(BoardSizeX);
        setBoardSizeY(BoardSizeY);
        createBoard();
        setMinesOnRandomFields();
        setNumbersBombNearby();
    }
    else error("ERROR! StartBoardMenagement Failed. CheckArgs return false!. ");
}

std::vector<Location> MinesweeperBoard::getMinesLocation() const
{
    return bombLocation;
}
