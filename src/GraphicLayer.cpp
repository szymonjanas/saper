#include"GraphicLayer.hpp"
#include <iostream>

MSGraphicMouseConverter::MSGraphicMouseConverter(MinesweeperBoard* board)
{
    distanceBetweenFields = 10;
    distanceFromLeftEdge = 10;
    distanceFromTopEdge = 10;
    fieldSizeX = 30;
    fieldSizeY = 30;
    fieldCountX = board->getBoardWidth();
    fieldCountY = board->getBoardHeight();
}

sf::Vector2i MSGraphicMouseConverter::decodeMousePosition(int X, int Y)
{
    sf::Vector2i position;
    position.x = X;
    position.y = Y;
    int tab[2], i , counter;
    int x = 0, y = 0;
    for (i = 10, tab[0] = distanceFromLeftEdge, tab[1] = fieldSizeX+distanceFromLeftEdge, counter = 0; tab[1] <= fieldCountX*fieldSizeX + fieldCountX*distanceBetweenFields + distanceFromLeftEdge; ++counter)
    {
        if (position.x > tab[0] and position.x < tab[1])
            x = counter;
        tab[0] = tab[1] + distanceBetweenFields;
        tab[1] = tab[0] + fieldSizeX;
    }
    for (i = 10, tab[0] = distanceFromTopEdge, tab[1] = fieldSizeY+distanceFromTopEdge, counter = 0; tab[1] <= fieldCountY*fieldSizeY + fieldCountY*distanceBetweenFields + distanceFromTopEdge; ++counter)
    {
        if (position.y > tab[0] and position.y < tab[1])
            y = counter;
        tab[0] = tab[1] + distanceBetweenFields;
        tab[1] = tab[0] + fieldSizeY;
    }
    if (x >= 0 and y >= 0 and x < fieldCountX and y < fieldCountY)
    {
        position.x = x;
        position.y = y;
        return position;
    }
}

sf::Vector2i MSGraphicMouseConverter::codeFieldPosition(int X, int Y)
{
    sf::Vector2i position;
    int x, y;
    if (X == 0) x = 10;
    if (Y == 0) y = 10;
    if (X > 0) x = 10 + X*fieldSizeX + X*distanceBetweenFields;
    if (Y > 0) y = 10 + Y*fieldSizeY + Y*distanceBetweenFields;
    position.x = x;
    position.y = y;
    return position;
}



////////////////////////////////////////////////////////////////////////////

FieldShapeDrawingFactory::FieldShapeDrawingFactory(int fieldSizeX,
                                                   int fieldSizeY,
                                                   sf::RenderWindow* window,
                                                   MinesweeperBoard* board)
{
    this->fieldSizeX = fieldSizeX;
    this->fieldSizeY = fieldSizeY;
    this->window = window;
    this->board = board;
    this->converter = new MSGraphicMouseConverter (board);
}

FieldShapeDrawingFactory::~FieldShapeDrawingFactory()
{
    delete converter;
}

void FieldShapeDrawingFactory::showOnScreen()
{
    int x, y;
    for (int countY = 0; countY < board->getBoardHeight(); ++countY)
    {
        for (int countX = 0; countX < board->getBoardWidth(); ++countX)
        {
            x = converter->codeFieldPosition(countX, countY).x;
            y = converter->codeFieldPosition(countX, countY).y;
            switch (board->getFieldInfo(countX, countY))
            {
            case '#':
                drawField(Element::ERROR, x, y);
                break;
            case 'F':
                drawField(Element::FLAG, x, y);
                break;
            case '_':
                drawField(Element::NOT_REVEALED, x, y);
                break;
            case ' ':
                drawField(Element::EMPTY, x, y);
                break;
            case 'x':
                drawField(Element::MINE, x, y);
                break;
            default:
                drawField(Element::NUMBER, x, y);
                break;
            }
        }
    }
}

void FieldShapeDrawingFactory::drawField(Element element, int positionX, int positionY)
{
    switch(element)
    {
    case Element::ERROR:
        std::cerr << "ERROR SFML FIELD SHAPE FACTORY! CAN NOT DRAW THE SHAPE!" << std::endl;
        break;
    case Element::EMPTY:
        drawEmptyFieldShape(positionX, positionY);
        break;
    case Element::NOT_REVEALED:
        drawHiddenFieldShape(positionX, positionY);
        break;
    case Element::FLAG:
        drawFlagFieldShape(positionX, positionY);
        break;
    case Element::MINE:
        drawMineFieldShape(positionX, positionY);
        break;
    case Element::NUMBER:
            drawFieldWithNumberShape(board->countMines(positionX, positionY), positionX, positionY);
        break;
    case Element::BLOW_UP:

        for (int i = 1; i <= 6; ++i)
        {
            sf::Clock clock;
            bool check = true;
            while (check)
            {
                if (clock.getElapsedTime().asSeconds() > 0.1f)
                {
                    drawBlowUpTheBomb(i, positionX, positionY);
                    clock.restart();
                    check = false;
                }
            }
        }
        break;
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
    sf::RectangleShape rectangle;
    sf::Font font;
    if(!font.loadFromFile("../fonts/LatoBlack.ttf"))
        std::cerr << "ERROR! Font Load From File False!" << std::endl;
    sf::Text text(std::to_string(number), font, 18);
    text.setFillColor(sf::Color::Black);
    text.setPosition(posX+5, posY);
    window->draw(text);

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
