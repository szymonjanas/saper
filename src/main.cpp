#include <iostream>
#include <SFML/Window.h>
#include <SFML/Graphics.hpp>
#include"MinesweeperBoard.hpp"
#include"ConsoleLayer.hpp"
#include "GraphicLayer.hpp"
#include "GraphicControler.hpp"

int main()
{
    MinesweeperBoard board(8, 8, GameMode::EASY);
    //MSBoardTextView view (board);
    //MSTextControler ctrl (board, view);
    //ctrl.play();
    MSSFMLView view(&board);
    view.play();
}
