//#include "Menu.hpp"

//Menu::Menu()
//{}
//Menu::~Menu()
//{
//    delete board;
//    delete game;
//    delete window;
//}

//void Menu::turnOnGame(Layer layer)
//{
//    switch (layer)
//    {
//    case Layer::CONSOLE:
//        setConsoleLayer(ConsoleMenu());
//        break;
//    case Layer::GRAPHIC:
//        setGraphicLayer(GraphicMenu());
//        break;
//    }


//}

//void Menu::setGraphicLayer(GameMode level)
//{
//    delete window;
//    board = new GameManagement(level);
//    game = new GraphicLayer(board);
//    game->start();
//}

//void Menu::setConsoleLayer(GameMode level)
//{
//    board = new GameManagement (level);
//    game = new ConsoleLayer(board);
//    game->start();
//}

//void Menu::drawButton(float posX, float posY, std::string sign, sf::RenderWindow *window)
//{
//    sf::RectangleShape rectangle;
//    rectangle.setSize(sf::Vector2f(100, 40));
//    rectangle.setOutlineColor(sf::Color(140, 140, 140));
//    rectangle.setOutlineThickness(2);
//    rectangle.setFillColor(sf::Color(115, 115, 115));
//    rectangle.setPosition(posX, posY);
//    window->draw(rectangle);

//    sf::Font font;
//    if(!font.loadFromFile("../fonts/LatoBlack.ttf"))
//        std::cerr << "ERROR! Font Load From File False!" << std::endl;
//    sf::Text text(sign, font, 20);
//    text.setFillColor(sf::Color::Black);
//    text.setPosition(posX+10, posY+5);
//    window->draw(text);
//}

//Menu::Button Menu::decodePosition(int posX, int posY)
//{
//    if (posX >= 50 and posX <= 200){
//        if (posY >= 10 and posY <= 50) return Button::EASY;
//        if (posY >= 60 and posY <= 100) return Button::MEDIUM;
//        if (posY >= 110 and posY <= 150) return Button::HARD;
//        if (posY >= 160 and posY <= 200) return Button::EXIT;
//    }
//}

//GameMode Menu::GraphicMenu()
//{
//    int sizeX = 200;
//    int sizeY = 220;
//    window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), "SAPER MENU");
//    while (window->isOpen())
//    {
//        sf::Event event;
//        window->clear(sf::Color(160, 160, 160));
//        drawButton(50, 10, "EASY", window);
//        drawButton(50, 60, "MEDIUM", window);
//        drawButton(50, 110, "HARD", window);
//        drawButton(50, 160, "EXIT", window);
//        window->display();
//        while (window->pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//            {
//                exit(1);
//            }
//            if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
//            {
//                switch (decodePosition(event.mouseButton.x, event.mouseButton.y))
//                {
//                case Button::EASY:
//                    return GameMode::EASY;
//                    break;
//                case Button::MEDIUM:
//                    return GameMode::MEDIUM;
//                    break;
//                case Button::HARD:
//                    return GameMode::HARD;
//                    break;
//                case Button::EXIT:
//                    exit(1);
//                    break;
//                }
//            }
//        }
//    }
//}

//GameMode Menu::ConsoleMenu()
//{
//    std::cout << std::endl;
//    std::cout << "==========SAPER MENU==========" << std::endl;
//    std::cout << "=     Please select level    =" << std::endl;
//    std::cout << "=         1. EASY            =" << std::endl;
//    std::cout << "=         2. MEDIUM          =" << std::endl;
//    std::cout << "=         3. HARD            =" << std::endl;
//    std::cout << "=                            =" << std::endl;
//    std::cout << "=         0. EXIT            =" << std::endl;
//    std::cout << "==============================" << std::endl;
//    std::cout << "         YOUR CHOICE: "          << std::endl;
//    int i;
//    std::cin >> i;
//    switch(i)
//    {
//    case 1: return GameMode::EASY; break;
//    case 2: return GameMode::MEDIUM; break;
//    case 3: return GameMode::HARD; break;
//    case 0: exit(1); break;
//    }
//}
