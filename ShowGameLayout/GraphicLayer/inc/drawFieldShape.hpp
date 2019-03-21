#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window.h>
#include<SFML/Graphics.hpp>
#include "MessegesDebug.hpp"
#include <time.h>
#include <unistd.h>

class FieldShape
{
    sf::RectangleShape rectangle;
    sf::Texture texture;
    sf::Sprite shape;
public:
    void drawHiddenFieldShape(float posX, float posY, sf::RenderWindow* window);
    void drawEmptyFieldShape(float posX, float posY, sf::RenderWindow* window);
    void drawMineFieldShape(float posX, float posY, sf::RenderWindow* window);
    void drawFlagFieldShape(float posX, float posY, sf::RenderWindow* window);
    void drawFieldWithNumberShape(float posX, float posY, int number, sf::RenderWindow* window);
    sf::Sprite drawBlowUpTheBomb(int phase, float posX, float posY, sf::RenderWindow* window);

    void displayWinWindow();
    void displayLooseWindow();
};
