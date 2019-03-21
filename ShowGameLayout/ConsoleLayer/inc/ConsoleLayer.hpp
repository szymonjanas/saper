#pragma once

#include "GameManagement.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "MessegesDebug.hpp"
#include "Operations.hpp"
#include "Game.hpp"

class ConsoleLayer : virtual public Game
{
    GameManagement* game;

    //console service
    void clrscr();
    std::string prepareBoardToString();
    std::string getCharFromField(int X, int Y);
    std::string winScreen();
    std::string looseScreen();

    Vector2xy getLocationFromUser();
    OperationOnField getChooseFlagOrBomb();
    void showOnScreen(ShowStatus choose);

public:
    ConsoleLayer(GameManagement* Game);
    ~ConsoleLayer();
    void start() override;
};
