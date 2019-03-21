#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window.h>
#include<SFML/Graphics.hpp>
#include "GameDetailsLib.hpp"
#include "GameManagement.hpp"
#include "Operations.hpp"
#include <iostream>
#include "drawFieldShape.hpp"
#include "Game.hpp"

class GraphicLayer : virtual public Game
{
    sf::RenderWindow* window;
    GameManagement* game;
    FieldShape shape;

    sf::Vector2i decodeMousePosition(int X, int Y);
    void showOnScreen(sf::RenderWindow* window);

public:
    GraphicLayer(GameManagement* Game);
    ~GraphicLayer();

    void start() override;

};
