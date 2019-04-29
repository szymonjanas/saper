#pragma once

#include "MinesweeperBoardModel.hpp"

class MSBoardTextView
{
    MinesweeperBoard* board;
public:
    MSBoardTextView(MinesweeperBoard& board);
    void display();
};

class MSTextControler
{
    MinesweeperBoard* board;
    MSBoardTextView* view;
  public:
    MSTextControler(MinesweeperBoard&, MSBoardTextView&);
    void play();
};
