#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "MinesweeperBoardModel.hpp"
#include "Menu.hpp"
#include "GraphicControler.hpp"

int main()
{
    Menu menu;
    MinesweeperBoard* board = menu.getGameDetails();
    GraphicControler game(board);
    game.play();

    delete board;
}
