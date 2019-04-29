#include "Menu.hpp"

Menu::Menu()
{
    this->window = new sf::RenderWindow(sf::VideoMode(300, 230), "SAPER MENU");

    levelChecked = MenuElement::ERROR;
    sizeChecked = MenuElement::ERROR;

    buttons[0] = MenuButton(MenuElement::LEVEL_EASY, 10, 100, 80, 30);
    buttons[1] = MenuButton(MenuElement::LEVEL_MEDIUM, 10, 140, 80, 30);
    buttons[2] = MenuButton(MenuElement::LEVEL_HARD, 10, 180, 80, 30);
    buttons[3] = MenuButton(MenuElement::SIZE_SMALL, 110, 100, 80 , 30);
    buttons[3].boardX = 8; buttons[3].boardY = 8;
    buttons[4] = MenuButton(MenuElement::SIZE_MEDIUM, 110 ,140, 80, 30);
    buttons[4].boardX = 16; buttons[4].boardY = 16;
    buttons[5] = MenuButton(MenuElement::SIZE_LARGE, 110 ,180, 80, 30);
    buttons[5].boardX = 30; buttons[5].boardY = 16;
    buttons[6] = MenuButton(MenuElement::START, 210, 100, 80, 110);

}

Menu::~Menu()
{
    delete window;
}

void Menu::display()
{
    MenuFactory SAPER(250, 35, 20, window);
    SAPER.drawGameStatusInfo("          SAPER MENU", 25, 20);

    MenuFactory AUTOR(70, 30, 10, window);
    AUTOR.drawAuthorDetails(75, 70);

    MenuFactory LEVEL(80, 30, 12, window);
    LEVEL.drawLevelButton(buttons[0].isChecked, "    EASY", 10, 100);
    LEVEL.drawLevelButton(buttons[1].isChecked, " MEDIUM", 10, 140);
    LEVEL.drawLevelButton(buttons[2].isChecked, "    HARD", 10, 180);

    MenuFactory SIZE(80, 30, 12, window);
    SIZE.drawLevelButton(buttons[3].isChecked, "     8x8", 110, 100);
    SIZE.drawLevelButton(buttons[4].isChecked, "   16x16", 110, 140);
    SIZE.drawLevelButton(buttons[5].isChecked, "   30x16", 110, 180);

    MenuFactory START(80, 110, 16, window);
    START.drawSignButton(false, "\n\n START", 210, 100);
}

MenuElement Menu::mouseConverter(int X, int Y)
{
    for (int i = 0; i < 7; ++i)
        if (buttons[i].checkIsThisField(X, Y))
            return  buttons[i].name;
    return MenuElement::ERROR;
}

void Menu::changeElementStatus(MenuElement element)
{
    switch (element)
    {
    case MenuElement::LEVEL_EASY:
        levelChecked = MenuElement::LEVEL_EASY;
        break;
    case MenuElement::LEVEL_MEDIUM:
        levelChecked = MenuElement::LEVEL_MEDIUM;
        break;
    case MenuElement::LEVEL_HARD:
        levelChecked = MenuElement::LEVEL_HARD;
        break;
    case MenuElement::SIZE_SMALL:
        sizeChecked = MenuElement::SIZE_SMALL;
        break;
    case MenuElement::SIZE_MEDIUM:
        sizeChecked = MenuElement::SIZE_MEDIUM;
        break;
    case MenuElement::SIZE_LARGE:
        sizeChecked = MenuElement::SIZE_LARGE;
        break;
    }

    for (int i = 0; i < 7; ++i)
        buttons[i].isChecked = false;
    for (int i = 0; i < 7; ++i)
        if (buttons[i].name == levelChecked)
            buttons[i].isChecked = true;
    for (int i = 0; i < 7; ++i)
        if (buttons[i].name == sizeChecked)
            buttons[i].isChecked = true;
}

MinesweeperBoard* Menu::getGameDetails()
{
    MinesweeperBoard* board;
    while(window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit(1);
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            MenuElement mouseElement = mouseConverter(event.mouseButton.x, event.mouseButton.y);
            switch (event.mouseButton.button)
            {
                case sf::Mouse::Left:
                        if (mouseElement == MenuElement::START)
                            if (levelChecked != MenuElement::ERROR)
                                if (sizeChecked != MenuElement::ERROR)
                                {
                                    int boardSizeX;
                                    int boardSizeY;
                                    GameMode mode;
                                    for (int i = 0; i < 7; ++i)
                                        if (buttons[i].name == sizeChecked)
                                        {
                                            boardSizeX = buttons[i].boardX;
                                            boardSizeY = buttons[i].boardY;
                                        }
                                    switch (levelChecked)
                                    {
                                    case MenuElement::LEVEL_EASY:
                                        mode = GameMode::EASY;
                                        break;
                                    case MenuElement::LEVEL_MEDIUM:
                                        mode = GameMode::MEDIUM;
                                        break;
                                    case MenuElement::LEVEL_HARD:
                                        mode = GameMode::HARD;
                                        break;
                                    }
                                    board = new MinesweeperBoard(boardSizeX, boardSizeY, mode);
                                    window->close();
                                }
                        changeElementStatus(mouseElement);
                        break;
            }
        }
        window->clear(sf::Color(160, 160, 160));
        display();
        window->display();
    }
    return board;
}
