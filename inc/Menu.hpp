#pragma once
#include "Game.hpp"
#include "ConsoleLayer.hpp"
#include "GraphicLayer.hpp"
#include "GameManagement.hpp"
#include "Operations.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"


class Menu
{   
    GameManagement* board;
    Game* game;
    sf::RenderWindow* window;

    void setGraphicLayer(Level level);
    void setConsoleLayer(Level level);
    Level GraphicMenu();
    Level ConsoleMenu();

    //GRAPHIC
    void drawButton(float posX, float posY, std::string sign, sf::RenderWindow* window);
    enum class Button {EASY, MEDIUM, HARD, EXIT};
    Button decodePosition(int posX, int posY);

public:
    Menu();
    ~Menu();
    void turnOnGame(Layer layer);

};
