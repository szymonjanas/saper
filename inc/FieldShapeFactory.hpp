#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<time.h>

#include "MinesweeperBoardModel.hpp"
#include "MousePositionConverter.hpp"



enum class FieldElement{ERROR, EMPTY, NOT_REVEALED, FLAG, MINE, NUMBER, BLOW_UP};

class FieldShapeDrawingFactory
{
    sf::RenderWindow* window;
    MinesweeperBoard* board;
    MousePositionConverter* converter;

    int fieldSizeX;
    int fieldSizeY;

    void drawHiddenFieldShape(int posX, int posY);
    void drawEmptyFieldShape(int posX, int posY);
    void drawMineFieldShape(int posX, int posY);
    void drawFlagFieldShape(int posX, int posY);
    void drawFieldWithNumberShape(int number, int posX, int posY);
    void drawBlowUpTheBomb(int phase, int posX, int posY);
public:

    FieldShapeDrawingFactory(sf::RenderWindow* window,
                             MinesweeperBoard* board);
    ~FieldShapeDrawingFactory();
    void drawField(FieldElement element, int positionX, int positionY);
    void drawGameStatusInfo(std::string info, int posX, int posY, int screenSizeX);

};
