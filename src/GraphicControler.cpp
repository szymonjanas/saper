#include "GraphicControler.hpp"

MSSFMLView::MSSFMLView(MinesweeperBoard* board)
{
    this->board = board;
    fieldCountX = this->board->getBoardWidth();
    fieldCountY = this->board->getBoardHeight();
    distanceBetweenFields = 10;
    distanceFromLeftEdge = 10;
    distanceFromTopEdge = 10;
    fieldSizeX = 30;
    fieldSizeY = 30;
    window = new sf::RenderWindow(sf::VideoMode(board->getBoardWidth()*(fieldSizeX+distanceBetweenFields)+10,
                                                board->getBoardHeight()*(fieldSizeY+distanceBetweenFields)+10),
                                  "SAPER");
    drawElements = new FieldShapeDrawingFactory (fieldSizeX,
                                                 fieldSizeY,
                                                 window,
                                                 board);
    converter = new MSGraphicMouseConverter (board);
    window->clear(sf::Color(160, 160, 160));
}

MSSFMLView::~MSSFMLView()
{
    delete window;
    delete drawElements;
    delete converter;
}

void MSSFMLView::play()
{
    while(window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit(1);
        }
        while (board->getGameState() == GameState::RUNNING)
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    exit(1);

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i location = converter->decodeMousePosition(event.mouseButton.x, event.mouseButton.y);
                    int X = location.x;
                    int Y = location.y;

                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                                board->revealField(X, Y);
                                break;
                        case sf::Mouse::Right:
                                board->toggleFlag(X, Y);
                    }
                }
            }
            switch (board->getGameState())
            {
                case GameState::FINISHED_WIN:
                    std::cerr << "You WIN" << std::endl; break;
                case GameState::FINISHED_LOOSE:
                    std::cerr << "You LOOSE" << std::endl; break;
                case GameState::RUNNING: break;
            }
            window->clear(sf::Color(160, 160, 160));
            drawElements->showOnScreen();
            window->display();
        }
    }
}
