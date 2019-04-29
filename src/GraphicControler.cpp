#include "GraphicControler.hpp"
#include "TextView.hpp"
#include "GameSFMLSettings.hpp"
GraphicControler::GraphicControler(MinesweeperBoard* board)
{
    this->board = board;
    fieldCountX = this->board->getBoardWidth();
    fieldCountY = this->board->getBoardHeight();

    GameSFMLSettings settings;
    distanceBetweenFields = settings.getDistanceBetweenFields();
    distanceFromLeftEdge = settings.getDistanceFromLeftEdge();
    distanceFromTopEdge = settings.getDistanceFromTopEdge();
    fieldSizeX = settings.getFieldSizeX();
    fieldSizeY = settings.getFieldSizeY();

    screenSizeX = board->getBoardWidth()*(fieldSizeX+distanceBetweenFields)+10;
    screenSizeY = board->getBoardHeight()*(fieldSizeY+distanceBetweenFields)+10 + 60;

    window = new sf::RenderWindow(sf::VideoMode(screenSizeX, screenSizeY), "SAPER");
    drawElements = new GraphicView (board, window);
    converter = new MousePositionConverter (board);
    window->clear(sf::Color(160, 160, 160));
}

GraphicControler::~GraphicControler()
{
    delete window;
    delete drawElements;
    delete converter;
}

void GraphicControler::play()
{
    MSBoardTextView textview(*board);
    bool flagEnd = true;
    while(window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit(1);
        }
        bool flag = true;
        while (board->getGameState() == GameState::RUNNING)
        {
            if (flag)
            {
                board->debug_display();
                window->clear(sf::Color(160, 160, 160));
                drawElements->drawGameStatusInfo("WELCOME IN GAME" , screenSizeX);
                drawElements->showBoard();
                window->display();
                flag=false;
            }
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
                                break;
                    }
                    board->debug_display();
                    window->clear(sf::Color(160, 160, 160));
                    drawElements->drawGameStatusInfo("GAME RUNNING" , screenSizeX);
                    drawElements->showBoard();
                    window->display();
                }
            }

        }

        if (flagEnd)
        {
            window->clear(sf::Color(160, 160, 160));
            switch (board->getGameState())
            {
                case GameState::FINISHED_WIN:
                    drawElements->drawGameStatusInfo("YOU ARE WINNER!" , screenSizeX);
                    flagEnd = false; break;
                case GameState::FINISHED_LOOSE:
                    std::cout << "YOU LOOSE!" << std::endl;
                    drawElements->drawGameStatusInfo("YOU LOOSE!" , screenSizeX);
                    flagEnd = false; break;
                case GameState::RUNNING: break;
            }
            drawElements->showBoard();
            window->display();
        }
    }
}
