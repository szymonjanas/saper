#include "MinesweeperBoard.hpp"
#include <iostream>
#include <algorithm>
#include <stack>
static GameState stateOfGame;

MinesweeperBoard::MinesweeperBoard(int width,
                                   int heigh,
                                   GameMode mode) :
    width(width), heigh(heigh)
{
    mineCount = 0;
    stateOfGame = GameState::RUNNING;
    int mineMax = width * heigh;
    switch(mode)
    {
    case GameMode::EASY:
        mineCount = mineMax * 0.1;
        break;
    case GameMode::MEDIUM:
        mineCount = mineMax * 0.2;
        break;
    case GameMode::HARD:
        mineCount = mineMax * 0.3;
        break;
    case GameMode::DEBUG:
        break;
    }
    for (int ycount = 0; ycount < getBoardHeight(); ++ycount)
        for (int xcount = 0; xcount < getBoardWidth(); ++xcount){
            board[ycount][xcount] = Field();
        }
    if (mode == GameMode::EASY or mode == GameMode::MEDIUM or mode == GameMode::HARD)
    {
        srand(time(NULL));
        for (int mineCounter = 0; mineCounter < mineCount; ++mineCounter)
        {
            int X = rand() % getBoardWidth();
            int Y = rand() % getBoardHeight();
            if (!board[Y][X].hasMine) board[Y][X].hasMine = true;
            else --mineCounter;
        }
    }
    if (mode == GameMode::DEBUG)
    {
        for (int ycount = 0; ycount < getBoardHeight(); ++ycount)
            for (int xcount = 0; xcount < getBoardWidth(); ++xcount)
            {
                if (ycount == 0) board[ycount][xcount].hasMine = true;
                if ((ycount == 0 or ycount%2 == 0) and xcount == 0) board[ycount][xcount].hasMine = true;
                if (xcount == ycount) board[ycount][xcount].hasMine = true;
            }
    }
}

int MinesweeperBoard::getBoardWidth() const
{
    return width;
}

int MinesweeperBoard::getBoardHeight() const
{
    return heigh;
}

int MinesweeperBoard::getMineCount() const
{
    return mineCount;
}

int MinesweeperBoard::countMines(int x, int y) const
{
    /* Is checking place nerby:
     * 1 2 3
     * 4 X 5
     * 6 7 8
     * Is have a bomb.
     */
    if (!board[y][x].isRevealed) return -1;
    if (x < 0 or y < 0 or x >= getBoardWidth() or y >= getBoardHeight()) return -1;

    int numberOfMine = 0;
    for (int counterY = y - 1; counterY <= y + 1; ++counterY)
        if (counterY >= 0 and counterY < getBoardHeight())
            for (int counterX = x - 1; counterX <= x + 1; ++counterX)
                if (counterX >= 0 and counterX < getBoardWidth() and
                        board[counterY][counterX].hasMine)
                    ++numberOfMine;
    return numberOfMine;
}

bool MinesweeperBoard::hasFlag(int x, int y) const
{
    if (x < 0 or y < 0 or x >= getBoardWidth() or y >= getBoardHeight()) return false;
    if (board[y][x].hasFlag) return true;
    return false;
}

void MinesweeperBoard::toggleFlag(int x, int y)
{
    if ((x < 0 or y < 0 or x >= getBoardWidth() or y >= getBoardHeight()) or
        board[y][x].isRevealed or
            stateOfGame != GameState::RUNNING)
        return;
    if (board[y][x].hasFlag) board[y][x].hasFlag = false;
    else board[y][x].hasFlag = true;
}

void MinesweeperBoard::revealField(int x, int y)
{
    static bool firstMoveFlag = true;
    if (!(x < 0 or y < 0 or x >= getBoardWidth() or y >= getBoardHeight() or
          stateOfGame != GameState::RUNNING or
          board[y][x].hasFlag or
          board[y][x].isRevealed))
    {
        if (board[y][x].hasMine and firstMoveFlag)
        {

            bool isNotGoodLocationFlag = true;
            int X, Y;
            do
            {
                X = rand() % getBoardWidth();
                Y = rand() % getBoardHeight();
                if (!board[Y][X].hasMine) isNotGoodLocationFlag = false;
            } while (isNotGoodLocationFlag);
            board[y][x].hasMine = false;
            board[Y][X].hasMine = true;
            firstMoveFlag = false;
        }
        if (board[y][x].hasMine and !firstMoveFlag)
        {
            firstMoveFlag = false;
            board[y][x].isRevealed = true;
            stateOfGame = GameState::FINISHED_LOOSE;
            return;
        }

        board[y][x].isRevealed = true;
        if (countMines(x,y) == 0)
        {
            board[y][x].isRevealed = false;
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
                if (!board[Y][X].isRevealed)
                {
                    board[Y][X].isRevealed = true;

                    if (countMines(X,Y) == 0)
                    {
                        for (int counterY = Y - 1; counterY <= Y + 1; ++counterY)
                            for (int counterX = X - 1; counterX <= X + 1; ++counterX)
                                if (!(counterX < 0 or counterY < 0 or counterX >= getBoardWidth() or counterY >= getBoardHeight()))
                                    if (!board[counterY][counterX].isRevealed)
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
        else board[y][x].isRevealed = true;
    }
    firstMoveFlag = false;
}

bool MinesweeperBoard::isRevealed(int x, int y) const
{
    if (!(x < 0 or y < 0 or x >= getBoardWidth() or y >= getBoardHeight()))
        if (board[y][x].isRevealed) return true;
    return false;
}

GameState MinesweeperBoard::getGameState() const
{
    if (stateOfGame == GameState::FINISHED_LOOSE) return stateOfGame;

    int counterOfRightFlaggedMines = 0;
    int counterOfNotRevealField = 0;
    for (int ycount = 0; ycount < getBoardHeight(); ++ycount)
        for (int xcount = 0; xcount < getBoardWidth(); ++xcount)
        {
            if (!board[ycount][xcount].isRevealed) ++counterOfNotRevealField;
            if (board[ycount][xcount].hasFlag and board[ycount][xcount].hasMine) ++counterOfRightFlaggedMines;
        }
    if (counterOfRightFlaggedMines == 0) --counterOfRightFlaggedMines;
    if (    counterOfNotRevealField == getMineCount() or
            counterOfRightFlaggedMines == getMineCount()) stateOfGame = GameState::FINISHED_WIN;
    return stateOfGame;
}

char MinesweeperBoard::getFieldInfo(int x, int y) const
{
    if (x < 0 or y < 0 or x >= getBoardWidth() or y >= getBoardHeight()) return '#';
    if (!isRevealed(x,y) and hasFlag(x, y)) return 'F';
    if (!isRevealed(x,y)) return '_';
    if (isRevealed(x,y) and board[y][x].hasMine) return 'x';
    if (isRevealed(x,y) and countMines(x,y) == 0) return ' ';
    if (isRevealed(x,y) and countMines(x,y) > 0 and countMines(x,y) < 9) return (char)(48 + countMines(x,y));
    return 'E';
}

void MinesweeperBoard::debug_display() const
{
    for (int ycount = 0; ycount < getBoardHeight(); ++ycount)
    {
        if (ycount == 0) {
            std::cout << "  ";
            for (int xcount = 0; xcount < getBoardWidth(); ++xcount)
                std::cout << "[." << xcount << ".]";
            std::cout << std::endl;
        }
        for (int xcount = 0; xcount < getBoardWidth(); ++xcount)
        {
            if (xcount == 0)
            {
                if (ycount < 10) std::cout << " " << ycount;
                if (ycount >= 10) std::cout << ycount;
            }
            std::cout << "[";
            if (board[ycount][xcount].hasMine) std::cout << "M";
            else std::cout << ".";
            if (board[ycount][xcount].isRevealed) std::cout << "o";
            else std::cout << ".";
            if (board[ycount][xcount].hasFlag) std::cout << "f";
            else std::cout << ".";
            std::cout << "]";
        }
        std::cout << std::endl;
    }
}

