#pragma once
#include <iostream>
#include <SFML/Window.h>
#include <vector>
#include<SFML/Graphics.hpp>
#include<time.h>
#include<SFML/Window.hpp>
#include<SFML/Graphics.h>
#include"GraphicLayer.hpp"

class MSSFMLView
{
    sf::RenderWindow* window;
    MinesweeperBoard* board;
    FieldShapeDrawingFactory* drawElements;
    MSGraphicMouseConverter* converter;

    int distanceFromLeftEdge;
    int distanceFromTopEdge;
    int distanceBetweenFields;
    int fieldCountX;
    int fieldCountY;
    int fieldSizeX;
    int fieldSizeY;

public:
    MSSFMLView(MinesweeperBoard* board);
    ~MSSFMLView();
    void play();
};
