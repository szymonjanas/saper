#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class MenuFactory
{
    sf::RenderWindow* window;
    sf::Font font;

    int buttonSizeX;
    int buttonSizeY;
    unsigned int fontSize;
    int distanceTextFromLeft;
    int distanceTextFromTop;

    void drawButton(bool isChecked, int posX, int posY);
public:
    MenuFactory(int buttonSizeX,
                int buttonSizeY,
                unsigned int fontSize,
                sf::RenderWindow* window);

    void drawSignButton(bool isChecked, std::string Sign, int posX, int posY);
    void drawLevelButton (bool isChecked, std::string level, int posX, int posY);
    void drawAuthorDetails (int posX, int posY);

    void drawGameStatusInfo (std::string info, int posX, int posY);
};
