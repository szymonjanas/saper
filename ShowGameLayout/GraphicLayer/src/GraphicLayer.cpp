#include"GraphicLayer.hpp"

GraphicLayer::GraphicLayer(GameManagement* Game)
{
    game = Game;
    window = new sf::RenderWindow(sf::VideoMode(game->getSizeX()*20+game->getSizeX()*10+10, game->getSizeY()*20+game->getSizeY()*10+10), "SAPER");
}

GraphicLayer::~GraphicLayer()
{
    delete game;
    delete window;
}

void GraphicLayer::showOnScreen(sf::RenderWindow* window)
{
    for (int countY = 10, CountY = 1; CountY <= game->getSizeY(); countY += 30, ++CountY)
    {
        for (int countX = 10, CountX = 1; CountX <= game->getSizeX(); countX += 30, ++CountX)
        {
            switch (game->getFieldSign(CountX, CountY))
            {
            case FieldStatus::BLOW_UP:  window->draw(shape.drawBlowUpTheBomb(6, countX, countY, window));
                                        window->display();
                                        break;
            case FieldStatus::BOMB:     shape.drawMineFieldShape(countX, countY, window); break;
            case FieldStatus::NUMBER:   shape.drawFieldWithNumberShape(countX, countY, game->getNOBN(CountX, CountY), window); break;
            case FieldStatus::HIDDEN:   shape.drawHiddenFieldShape(countX, countY, window); break;
            case FieldStatus::EMPTY:    shape.drawEmptyFieldShape(countX, countY, window); break;
            case FieldStatus::FLAG:     shape.drawFlagFieldShape(countX, countY, window); break;
            }
        }
    }
}

sf::Vector2i GraphicLayer::decodeMousePosition(int X, int Y)
{
    sf::Vector2i position;
    position.x = X;
    position.y = Y;
    int tab[2], i , counter;
    int x = 0, y = 0;
    for (i = 10, tab[0] = 10, tab[1] = 30, counter = 1; tab[1] <= game->getSizeX()*30; ++counter)
    {
        if (position.x > tab[0] and position.x < tab[1])
            x = counter;

        tab[0] = tab[1] + 10;
        tab[1] = tab[0] + 20;
    }
    for (i = 10, tab[0] = 10, tab[1] = 30, counter = 1; tab[1] <= game->getSizeY()*30; ++counter)
    {
        if (position.y > tab[0] and position.y < tab[1])
            y = counter;

        tab[0] = tab[1] + 10;
        tab[1] = tab[0] + 20;
    }
    debug::cerr("Mouse Click X: " + std::to_string(X) + "Mouse Click Y: " + std::to_string(Y));
    debug::cerr("Mouse Decode X: " + std::to_string(x) + "Mouse Decode Y: " + std::to_string(y));

    if (x != 0 and y != 0 and game->isFieldOnTheBoard(x, y))
    {
        position.x = x;
        position.y = y;

        return position;
    }
    debug::cerr("ERROR! Wrong Mouse Position Given!");
}

void GraphicLayer::start()
{
    while(window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit(1);
        }
        while (game->checkGameStatus() == GameStatus::RUNNING)
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    exit(1);

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i location = decodeMousePosition(event.mouseButton.x, event.mouseButton.y);
                    int X = location.x;
                    int Y = location.y;

                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                                if (!game->checkAndSetField(X,Y))
                                {

                                }
                                break;
                        case sf::Mouse::Right:
                            if (game->isFlag(X,Y))
                                game->removeFlag(X,Y);
                            else
                                game->makeFlag(X,Y); break;
                    }
                }
            }
            switch (game->checkGameStatus())
            {
                case GameStatus::FINISH_WIN:
                    game->setAllFieldsNotHidden();
                    window->display();
                    shape.displayWinWindow();
                    debug::cerr("You WIN"); break;
                case GameStatus::FINISH_LOOSE:
                    Vector2xy blowUp = game->getBlowUp();
                    blowUp.x = (blowUp.x-1)*20+(blowUp.x-1)*10+10;
                    blowUp.y = (blowUp.y-1)*20+(blowUp.y-1)*10+10;
                    for (int i = 1; i <= 6; ++i)
                    {
                        bool check = true;
                        sf::Clock clock;
                        while (check)
                        {
                            if (clock.getElapsedTime().asSeconds() > 0.1f)
                            {
                                shape.drawEmptyFieldShape(blowUp.x, blowUp.y, window);
                                window->draw(shape.drawBlowUpTheBomb(i, blowUp.x, blowUp.y, window));
                                window->display();
                                clock.restart();
                                check = false;
                            }
                        }
                    }
                    game->setAllFieldsNotHidden();
                    window->display();
                    shape.displayLooseWindow();
                    debug::cerr("You LOOSE"); break;
            }

            window->clear(sf::Color(160, 160, 160));
            showOnScreen(window);
            window->display();
        }
    }
}
