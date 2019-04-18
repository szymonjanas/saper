#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<time.h>

#include "MinesweeperBoard.hpp"

class MSGraphicMouseConverter
{
    int distanceFromLeftEdge;
    int distanceFromTopEdge;
    int distanceBetweenFields;
    int fieldCountX;
    int fieldCountY;
    int fieldSizeX;
    int fieldSizeY;

  public:
    MSGraphicMouseConverter(MinesweeperBoard* board);
    sf::Vector2i decodeMousePosition(int X, int Y);
    sf::Vector2i codeFieldPosition(int X, int Y);
};

enum class Element{ERROR, EMPTY, NOT_REVEALED, FLAG, MINE, NUMBER, BLOW_UP};

class FieldShapeDrawingFactory
{
    sf::RenderWindow* window;
    MinesweeperBoard* board;
    MSGraphicMouseConverter* converter;

    int fieldSizeX;
    int fieldSizeY;

    void drawHiddenFieldShape(int posX, int posY);
    void drawEmptyFieldShape(int posX, int posY);
    void drawMineFieldShape(int posX, int posY);
    void drawFlagFieldShape(int posX, int posY);
    void drawFieldWithNumberShape(int number, int posX, int posY);
    void drawBlowUpTheBomb(int phase, int posX, int posY);

    void drawField(Element element, int positionX, int positionY);

public:

    FieldShapeDrawingFactory(int fieldSizeX,
                             int fieldSizeY,
                             sf::RenderWindow* window,
                             MinesweeperBoard* board);
    ~FieldShapeDrawingFactory();
    void showOnScreen();
};
