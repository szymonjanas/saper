#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "MenuFactory.hpp"
#include "MinesweeperBoardModel.hpp"

enum class MenuElement {LEVEL_EASY,
                        LEVEL_MEDIUM,
                        LEVEL_HARD,
                        SIZE_SMALL,
                        SIZE_MEDIUM,
                        SIZE_LARGE,
                        START,
                        ERROR};

enum class GameLevel { EASY, MEDIUM, HARD };

struct MenuButton
{
    MenuElement name;
    bool isChecked;
    int locationX;
    int locationY;
    int sizeX;
    int sizeY;

    int boardX;
    int boardY;

    MenuButton(MenuElement name, int locationX, int locationY, int sizeX, int sizeY) :
        name(name), locationX(locationX), locationY(locationY), sizeX(sizeX), sizeY(sizeY) {
        isChecked = false;
    }
    MenuButton(){;}
    bool checkIsThisField(int X, int Y)
    {
        if (X >= locationX and X <= locationX+sizeX)
            if (Y >= locationY and Y <= locationY+sizeY)
                return true;
        return false;
    }
    void changeStatus()
    {
        if (!isChecked) isChecked = true;
        if (isChecked) isChecked = false;
    }
};

class Menu
{
    MenuButton buttons[7];
    sf::RenderWindow* window;

    MenuElement levelChecked;
    MenuElement sizeChecked;

    bool isLevelCheck;
    GameLevel level;

    bool isBoardCheck;
    sf::Vector2i sizeBoard;

    bool isStartedFlag;

    MenuElement mouseConverter(int X, int Y);
    void changeElementStatus(MenuElement element); //TO DO

    bool canStart() const; // TO DO
    void display(); // TO FINISH

public:
    Menu();
    ~Menu();

    MinesweeperBoard* getGameDetails(); // TO FINISH
};


