#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <vector>
#include<SFML/Graphics.hpp>
#include<time.h>
#include"GraphicView.hpp"
#include "GraphicView.hpp"
#include "MousePositionConverter.hpp"

class GraphicControler
{
    sf::RenderWindow* window;
    MinesweeperBoard* board;
    GraphicView* drawElements;
    MousePositionConverter* converter;

    int distanceFromLeftEdge;
    int distanceFromTopEdge;
    int distanceBetweenFields;
    int fieldCountX;
    int fieldCountY;
    int fieldSizeX;
    int fieldSizeY;

    int screenSizeX;
    int screenSizeY;

public:
    GraphicControler(MinesweeperBoard* board);
    ~GraphicControler();
    void play();
};


