#include "drawFieldShape.hpp"

void FieldShape::drawHiddenFieldShape(float posX, float posY, sf::RenderWindow* window)
{
    rectangle.setSize(sf::Vector2f(20, 20));
    rectangle.setOutlineColor(sf::Color(140, 140, 140));
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color(115, 115, 115));
    rectangle.setPosition(posX, posY);
    window->draw(rectangle);
}

void FieldShape::drawEmptyFieldShape(float posX, float posY, sf::RenderWindow* window)
{
    rectangle.setSize(sf::Vector2f(20, 20));
    rectangle.setOutlineColor(sf::Color(160, 160, 160));
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color(160, 160, 160));
    rectangle.setPosition(posX, posY);
    window->draw(rectangle);
}

void FieldShape::drawMineFieldShape(float posX, float posY, sf::RenderWindow* window)
{
    sf::Texture texture;
    if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(0, 0, 20, 20)))
        debug::cerr("Texture Not Loaded!");
    texture.setSrgb(true);
    if (!texture.isSrgb()) debug::cerr("IS NOT SRGB!");
    sf::Sprite shape;
    shape.setPosition(posX, posY);
    shape.setTexture(texture);
    window->draw(shape);
}

void FieldShape::drawFlagFieldShape(float posX, float posY, sf::RenderWindow* window)
{
    rectangle.setSize(sf::Vector2f(20, 20));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setPosition(posX, posY);
    window->draw(rectangle);
}

void FieldShape::drawFieldWithNumberShape(float posX, float posY, int number, sf::RenderWindow* window)
{

    sf::Font font;
    if(!font.loadFromFile("../fonts/LatoBlack.ttf"))
        std::cerr << "ERROR! Font Load From File False!" << std::endl;
    sf::Text text(std::to_string(number), font, 18);
    text.setFillColor(sf::Color::Black);
    text.setPosition(posX+5, posY);
    window->draw(text);

    rectangle.setSize(sf::Vector2f(20, 20));
    rectangle.setOutlineColor(sf::Color(140, 140, 140));
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setPosition(posX, posY);
    window->draw(rectangle);
}

sf::Sprite FieldShape::drawBlowUpTheBomb(int phase, float posX, float posY, sf::RenderWindow *window)
{
    shape.setPosition(posX, posY);
        switch (phase)
        {
        case 1:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(0, 0, 20, 20)))
                debug::cerr("Texture Not Loaded!");
            break;
        case 2:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(20, 0, 40, 20)))
                debug::cerr("Texture Not Loaded!");
            break;
        case 3:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(0, 20, 20, 40)))
                debug::cerr("Texture Not Loaded!");
            break;
        case 4:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(20, 20, 40, 40)))
                debug::cerr("Texture Not Loaded!");
            break;
        case 5:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(40, 0, 60, 20)))
                debug::cerr("Texture Not Loaded!");
            break;
        case 6:
            if(!texture.loadFromFile("../textures/blow.png", sf::IntRect(40, 20, 60, 40)))
                debug::cerr("Texture Not Loaded!");
            break;
        }

    texture.setSrgb(true);
    if (!texture.isSrgb()) debug::cerr("IS NOT SRGB!");
    shape.setTexture(texture);
    return shape;

}

void FieldShape::displayWinWindow()
{
    sf::RenderWindow window(sf::VideoMode(250,120), "WIN SCREEN");

    sf::Font font;
    if(!font.loadFromFile("../fonts/LatoBlack.ttf"))
        std::cerr << "ERROR! Font Load From File False!" << std::endl;
    sf::Text text("Congratulacion You Win!", font, 25);
    text.setFillColor(sf::Color::Black);
    text.setPosition(35, 40);


    rectangle.setSize(sf::Vector2f(200, 80));
    rectangle.setOutlineColor(sf::Color(140, 140, 140));
    rectangle.setOutlineThickness(3);
    rectangle.setFillColor(sf::Color(115, 115, 115));
    rectangle.setPosition(25,20);

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(160, 160, 160));
        window.draw(rectangle);
        window.draw(text);
        window.display();
    }
}

void FieldShape::displayLooseWindow()
{
    sf::RenderWindow window(sf::VideoMode(250,120), "LOOSE SCREEN");

    sf::Font font;
    if(!font.loadFromFile("../fonts/LatoBlack.ttf"))
        std::cerr << "ERROR! Font Load From File False!" << std::endl;
    sf::Text text("Sorry You Loose!", font, 20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(35, 40);


    rectangle.setSize(sf::Vector2f(200, 80));
    rectangle.setOutlineColor(sf::Color(140, 140, 140));
    rectangle.setOutlineThickness(3);
    rectangle.setFillColor(sf::Color(115, 115, 115));
    rectangle.setPosition(25,20);

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(160, 160, 160));
        window.draw(rectangle);
        window.draw(text);
        window.display();
    }
}
