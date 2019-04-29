#include"FieldShapeFactory.hpp"
#include "GameSFMLSettings.hpp"

#include <iostream>

FieldShapeDrawingFactory::FieldShapeDrawingFactory(sf::RenderWindow* window,
                                                   MinesweeperBoard* board)
{
    GameSFMLSettings settings;
    this->fieldSizeX = settings.getFieldSizeX();
    this->fieldSizeY = settings.getFieldSizeY();
    this->window = window;
    this->board = board;
    converter = new MousePositionConverter (board);
}

FieldShapeDrawingFactory::~FieldShapeDrawingFactory()
{
    delete converter;
}

void FieldShapeDrawingFactory::drawField(FieldElement element, int positionX, int positionY)
{
    switch(element)
    {
    case FieldElement::ERROR:
        std::cerr << "ERROR SFML FIELD SHAPE FACTORY! CAN NOT DRAW THE SHAPE!" << std::endl;
        break;
    case FieldElement::EMPTY:
        drawEmptyFieldShape(positionX, positionY);
        break;
    case FieldElement::NOT_REVEALED:
        drawHiddenFieldShape(positionX, positionY);
        break;
    case FieldElement::FLAG:
        drawFlagFieldShape(positionX, positionY);
        break;
    case FieldElement::MINE:
        drawMineFieldShape(positionX, positionY);
        break;
    case FieldElement::NUMBER:
        int x = converter->decodeMousePosition(positionX, positionY).x;
        int y = converter->decodeMousePosition(positionX, positionY).y;
        drawFieldWithNumberShape((int)board->getFieldInfo(x, y)-48, positionX, positionY);
        break;
//    case FieldElement::BLOW_UP:
//        for (int i = 1; i <= 6; ++i)
//        {
//            sf::Clock clock;
//            bool check = true;
//            while (check)
//            {
//                if (clock.getElapsedTime().asSeconds() > 0.1f)
//                {
//                    drawBlowUpTheBomb(i, positionX, positionY);
//                    clock.restart();
//                    check = false;
//                }
//            }
//        }
//        break;
    }
}

void FieldShapeDrawingFactory::drawHiddenFieldShape(int posX, int posY)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setOutlineColor(sf::Color(140, 140, 140));
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color(115, 115, 115));
    rectangle.setPosition(posX, posY);
    window->draw(rectangle);
}

void FieldShapeDrawingFactory::drawEmptyFieldShape(int posX, int posY)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setOutlineColor(sf::Color(160, 160, 160));
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color(160, 160, 160));
    rectangle.setPosition(posX, posY);
    window->draw(rectangle);
}

void FieldShapeDrawingFactory::drawMineFieldShape(int posX, int posY)
{
    sf::Texture texture;
    if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(0, 0, 20, 20)))
        std::cerr << "Texture Not Loaded!" << std::endl;
    texture.setSrgb(true);
    if (!texture.isSrgb()) std::cerr << "IS NOT SRGB!" << std::endl;
    sf::Sprite shape;
    shape.setPosition(posX, posY);
    shape.setTexture(texture);
    window->draw(shape);
}

void FieldShapeDrawingFactory::drawFlagFieldShape(int posX, int posY)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setPosition(posX, posY);
    window->draw(rectangle);
}

void FieldShapeDrawingFactory::drawFieldWithNumberShape(int number, int posX, int posY)
{
    sf::Font font;
    if(!font.loadFromFile("../fonts/LatoBlack.ttf"))
        std::cerr << "ERROR! Font Load From File False!" << std::endl;

    sf::Text text(std::to_string(number), font, 18);
    text.setFillColor(sf::Color::Black);
    text.setPosition(posX+5, posY);
    window->draw(text);

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setOutlineColor(sf::Color(140, 140, 140));
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setPosition(posX, posY);
    window->draw(rectangle);
}

void FieldShapeDrawingFactory::drawBlowUpTheBomb(int phase, int posX, int posY)
{
    sf::Texture texture;
    sf::Sprite shape;
    shape.setPosition(posX, posY);
        switch (phase)
        {
        case 1:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(0, 0, 20, 20)))
                std::cerr << "Texture Not Loaded!" << std::endl;
            break;
        case 2:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(20, 0, 40, 20)))
                std::cerr << "Texture Not Loaded!" << std::endl;
            break;
        case 3:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(0, 20, 20, 40)))
                std::cerr << "Texture Not Loaded!" << std::endl;
            break;
        case 4:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(20, 20, 40, 40)))
                std::cerr << "Texture Not Loaded!" << std::endl;
            break;
        case 5:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(40, 0, 60, 20)))
                std::cerr << "Texture Not Loaded!" << std::endl;
            break;
        case 6:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(40, 20, 60, 40)))
                std::cerr << "Texture Not Loaded!" << std::endl;
            break;
        }

    texture.setSrgb(true);
    shape.setTexture(texture);
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setOutlineColor(sf::Color(160, 160, 160));
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color(160, 160, 160));
    rectangle.setPosition(posX, posY);
    window->draw(rectangle);
    window->draw(shape);
}

void FieldShapeDrawingFactory::drawGameStatusInfo(std::string info, int posX, int posY, int screenSizeX)
{
    sf::Font font;
    if(!font.loadFromFile("../fonts/LatoBlack.ttf"))
        std::cerr << "ERROR! Font Load From File False!" << std::endl;

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(screenSizeX-20, 30));
    rectangle.setOutlineColor(sf::Color(140, 140, 140));
    rectangle.setOutlineThickness(2);
    rectangle.setPosition(posX, posY);
    rectangle.setFillColor(sf::Color(165, 210, 100));

    sf::Text text(info, font, 18);
    text.setFillColor(sf::Color::Black);
    text.setPosition(posX+10, posY+5);

    window->draw(rectangle);
    window->draw(text);
}
