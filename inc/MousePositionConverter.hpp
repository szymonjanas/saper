#pragma once
#include<SFML/Window.hpp>
#include"MinesweeperBoardModel.hpp"

class MousePositionConverter
{
    int distanceFromLeftEdge;
    int distanceFromTopEdge;
    int distanceBetweenFields;
    int fieldCountX;
    int fieldCountY;
    int fieldSizeX;
    int fieldSizeY;

  public:
    MousePositionConverter(MinesweeperBoard* board);
    sf::Vector2i decodeMousePosition(int X, int Y);
    sf::Vector2i codeFieldPosition(int X, int Y);
};
