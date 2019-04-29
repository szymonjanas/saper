#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"MinesweeperBoardModel.hpp"
#include"ConsoleLayer.hpp"
#include "GraphicView.hpp"
#include "GraphicControler.hpp"

int main()
{
    MinesweeperBoard board(GameMode::DEBUG);
    MSBoardTextView view (board);
    MSTextControler ctrl (board, view);
    ctrl.play();

}
