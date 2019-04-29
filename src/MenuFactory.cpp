#include "MenuFactory.hpp"

MenuFactory::MenuFactory(int buttonSizeX,
                         int buttonSizeY,
                         unsigned int fontSize,
                         sf::RenderWindow* window)
{
    this->buttonSizeX = buttonSizeX;
    this->buttonSizeY = buttonSizeY;
    this->window = window;
    this->fontSize = fontSize;
    font.loadFromFile("../fonts/LatoBlack.ttf");

    distanceTextFromLeft = 10;
    distanceTextFromTop = 5;

}

void MenuFactory::drawButton(bool isChecked, int posX, int posY)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(buttonSizeX, buttonSizeY));
    rectangle.setOutlineColor(sf::Color(140, 140, 140));
    rectangle.setOutlineThickness(2);
    if (!isChecked)
        rectangle.setFillColor(sf::Color(115, 115, 115));
    if (isChecked)
        rectangle.setFillColor(sf::Color(40, 240, 65));
    rectangle.setPosition(posX, posY);
    window->draw(rectangle);
}

void MenuFactory::drawSignButton(bool isChecked, std::string Sign, int posX, int posY)
{
    drawButton(isChecked, posX, posY);
    sf::Text text(Sign, font, fontSize);
    text.setFillColor(sf::Color::Black);
    text.setPosition(posX+distanceTextFromLeft, posY+distanceTextFromTop);
    window->draw(text);
}

void MenuFactory::drawLevelButton(bool isChecked, std::string level, int posX, int posY)
{
    drawButton(isChecked, posX, posY);
    sf::Text text(level, font, fontSize);
    text.setFillColor(sf::Color::Black);
    text.setPosition(posX+distanceTextFromLeft, posY+distanceTextFromTop);
    window->draw(text);
}

void MenuFactory::drawAuthorDetails(int posX, int posY)
{
    std::string author = "Szymon Janas 249271 wt 15:15";
    sf::Text text(author, font, fontSize);
    text.setFillColor(sf::Color::Black);
    text.setPosition(posX, posY);
    window->draw(text);
}

void MenuFactory::drawGameStatusInfo(std::string info, int posX, int posY)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(buttonSizeX, buttonSizeY));
    rectangle.setOutlineColor(sf::Color(140, 140, 140));
    rectangle.setOutlineThickness(2);
    rectangle.setPosition(posX, posY);
    rectangle.setFillColor(sf::Color(165, 210, 100));

    sf::Text text(info, font, fontSize);
    text.setFillColor(sf::Color::Black);
    text.setPosition(posX+distanceTextFromLeft, posY+distanceTextFromTop);

    window->draw(rectangle);
    window->draw(text);
}
