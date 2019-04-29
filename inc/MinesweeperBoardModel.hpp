#pragma once

#include<iostream>

enum class GameMode
{
    EASY,
    MEDIUM,
    HARD,
    DEBUG
};

enum class GameState
{
    RUNNING,
    FINISHED_WIN,
    FINISHED_LOOSE
};

struct Field
{
    Field(){
        hasMine = false;
        hasFlag = false;
        isRevealed = false;
        numberOfBombNearby = 0;
    }
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
    int numberOfBombNearby;
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
    Field board[100][100];

    int mineCount;
    const int width;
    const int heigh;

 public:
    MinesweeperBoard(int width,
                     int heigh,
                     GameMode mode);
    MinesweeperBoard(GameMode mode);

    int getMineCount() const;
    int getBoardWidth() const;
    int getBoardHeight() const;
    int countMines(int x, int y) const;

    bool hasFlag(int x, int y) const;
    void toggleFlag(int x, int y);

    void revealField(int x, int y);
    bool isRevealed(int x, int y) const;

    GameState getGameState() const;
    char getFieldInfo(int x, int y) const;

    void debug_display() const;

};
