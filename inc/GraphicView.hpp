#pragma once

#include"FieldShapeFactory.hpp"
#include"MinesweeperBoardModel.hpp"
#include "MousePositionConverter.hpp"
#include "Menu.hpp"

class GraphicView
{
    sf::RenderWindow* window;
    MinesweeperBoard* board;
    FieldShapeDrawingFactory* factory;
    MousePositionConverter* converter;

public:
    GraphicView(MinesweeperBoard* board,
                sf::RenderWindow* window);
    GraphicView(sf::RenderWindow* window);
    ~GraphicView();
    void drawGameStatusInfo(std::string gameStatusInfo, int screenSizeX);
    void showBoard();
};
