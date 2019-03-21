#include "GameManagement.hpp"
#include "GameDetailsLib.hpp"
#include <iostream>

GameManagement::GameManagement(Level level)
{
    GameDetails gameDetails(level);
    if (level != Level::USER)
    {
        game = new MinesweeperBoard(gameDetails.getMineQuantity(),
                                    gameDetails.getSizeX(),
                                    gameDetails.getSizeY());
    }
    else debug::cerr("ERROR! Level should Not be USER!");

}
GameManagement::GameManagement(Level level,
                               int BoardSizeX,
                               int BoardSizeY,
                               int MineQuantity)
{
    if (level == Level::USER){
        if (checkIsSizeAndMineQuantityInRange(BoardSizeX, BoardSizeY, MineQuantity))
            game = new MinesweeperBoard(MineQuantity,
                                        BoardSizeX,
                                        BoardSizeY);
    }
    else debug::cerr("ERROR! Value Given are not agree with Level! Level is Not USER!");
}

GameManagement::GameManagement(MinesweeperBoard& board)
{
    game = &board;
}

GameManagement::~GameManagement()
{
    delete game;
}

bool GameManagement::incrementFlagsNumber()
{
    if (flagsNumber < game->getMineCount())
    {
        ++flagsNumber;
        return true;
    }
    return false;
}

bool GameManagement::decrementFlagsNumber()
{
    if (flagsNumber > 0)
    {
        --flagsNumber;
        return true;
    }
    return false;
}

int GameManagement::getSizeX() const
{
    return game->getBoardWidth();
}

int GameManagement::getSizeY() const
{
    return game->getBoardHeight();
}

int GameManagement::getMineQuantity() const
{
    return game->getMineCount();
}

Vector2xy GameManagement::getBlowUp() const
{
    return blowUp;
}

bool GameManagement::checkIsSizeAndMineQuantityInRange( int &BoardSizeX,
                                                        int &BoardSizeY,
                                                        int &MineQuantity)
{
    MinMaxFieldSizeAndMineQuantity checkSize;
    if (BoardSizeX > checkSize.MaxBoardSizeX or BoardSizeX < checkSize.MinBoardSizeX)
        {
            debug::cerr("Wrong SizeX of Board!");
            return false;
        }
    if (BoardSizeY > checkSize.MaxBoardSizeY or BoardSizeY < checkSize.MinBoardSizeY)
        {
            debug::cerr("Wrong SizeY of Board!");
            return false;
        }
    if (MineQuantity > checkSize.MaxMineQuantity or MineQuantity < checkSize.MinMineQuantity)
        {
            debug::cerr("Wrong MineQuantity - out of range!");
            return false;
        }
    if ((BoardSizeX - 1) * (BoardSizeY - 1) < MineQuantity)
        {
            debug::cerr("Wrong proportions of MineQuantity to Board size!");
            return false;
        }
    return true;
}

int GameManagement::scores()
{
    int score = 0;
    for (int countY = 1; countY <= getSizeY(); ++countY)
    {
        for (int countX = 1; countX <= getSizeX(); ++countX)
        {
           if(game->isMineOnField(countX, countY) and game->isFlagOnField(countX, countY)) ++score;
        }
    }
    return score;
}

void GameManagement::makeFlag(int X, int Y)
{
    if (    game->checkIsFieldOnBoard(X, Y) and
            game->isHidden(X, Y) and
            !game->isFlagOnField(X, Y))
        if (incrementFlagsNumber())
                game->setFlagOnField(X, Y);
}

void GameManagement::removeFlag(int X, int Y)
{
    if (    game->checkIsFieldOnBoard(X, Y) and
            game->isFlagOnField(X, Y) and
            decrementFlagsNumber())
                game->removeFlagFromField(X, Y);
}

bool GameManagement::isFlag(int X, int Y) const
{
    if(game->checkIsFieldOnBoard(X, Y))
        if (game->isFlagOnField(X, Y))
            return true;
    return false;
}

FieldStatus GameManagement::getFieldSign(int X, int Y)
{
    if (game->checkIsFieldOnBoard(X, Y)){
        if (!game->isHidden(X, Y) and game->isMineOnField(X, Y) and getBlowUp().x == X and getBlowUp().y == Y) return FieldStatus::BLOW_UP;
        if (!game->isHidden(X, Y) and game->isMineOnField(X, Y)) return FieldStatus::BOMB;
        if (game->isFlagOnField(X, Y)) return FieldStatus::FLAG;
        if (game->isHidden(X, Y)) return FieldStatus::HIDDEN;
        if (!game->isHidden(X, Y) and game->isNOBN(X, Y)) return FieldStatus::NUMBER;
        if (!game->isHidden(X, Y) and !game->isNOBN(X, Y)) return FieldStatus::EMPTY;
    }
    return FieldStatus::ERROR;
}

int GameManagement::getNOBN(int X, int Y) const
{
    if (game->checkIsFieldOnBoard(X, Y) and game->isNOBN(X, Y))
        return game->getNOBN(X, Y);
}

bool GameManagement::checkAndSetField(int X, int Y)
{
    if (!game->isFlagOnField(X, Y) and game->isMineOnField(X, Y)){
        game->setNotHidden(X, Y);
        blowUp.x = X;
        blowUp.y = Y;
        return false;
    }
    if (!game->isFlagOnField(X, Y) and game->isNOBN(X, Y)) game->setNotHidden(X, Y);
    if (!game->isFlagOnField(X, Y) and !game->isNOBN(X, Y)) game->showEmptyFieldNearby(X, Y);
    return true;
}

GameStatus GameManagement::checkGameStatus()
{
    int counterForFlags = 0;
    for (const auto& local : game->getMinesLocation())
    {
        if (game->isMineOnField(local.x, local.y) == game->isFlagOnField(local.x, local.y))
            ++counterForFlags;
        if (counterForFlags == game->getMineCount()) return GameStatus::FINISH_WIN;
        if (game->isMineOnField(local.x, local.y) and !game->isHidden(local.x ,local.y)) return GameStatus::FINISH_LOOSE;
    }
    int counter = 0;
    for (int countY = 1; countY <= game->getBoardHeight(); ++countY)
        for (int countX = 1; countX <= game->getBoardWidth(); ++countX){
            if (game->isHidden(countX, countY)) ++counter;
            if (game->isHidden(countX, countY) and !game->isMineOnField(countX, countY))
                return GameStatus::RUNNING;
        }
    if (counter == game->getMineCount()) return GameStatus::FINISH_WIN;

    return GameStatus::RUNNING;
}

bool GameManagement::isFieldOnTheBoard(int X, int Y)
{
    return game->checkIsFieldOnBoard(X, Y);
}

void GameManagement::setAllFieldsNotHidden()
{
    for (int countY = 1; countY <= game->getBoardHeight(); ++countY)
        for (int countX = 1; countX <= game->getBoardWidth(); ++countX)
            game->setNotHidden(countX, countY);
}

void GameManagement::debug_display(MinesweeperBoard* board)
{
    if (debug::getDebugStatus())
    {
        std::cout << "Bombs: " << std::endl;
        std::cout << " ";
        for (int counter = 1; counter <= board->getBoardWidth(); ++counter) std::cout << " " << counter;
        std::cout << std::endl;
        for (int sY = 1; sY <= board->getBoardHeight(); ++sY)
        {
            std::cout << sY;
            for (int sX = 1; sX <= board->getBoardWidth(); ++sX)
            {
               std::cout << " " << board->isMineOnField(sX, sY);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "NOBN: " << std::endl;
        std::cout << " ";
        for (int counter = 1; counter <= board->getBoardWidth(); ++counter) std::cout << " " << counter;
        std::cout << std::endl;
        for (int sY = 1; sY <= board->getBoardHeight(); ++sY)
        {
            std::cout << sY;
            for (int sX = 1; sX <= board->getBoardWidth(); ++sX)
            {
               std::cout << " " << board->getNOBN(sX, sY);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}
