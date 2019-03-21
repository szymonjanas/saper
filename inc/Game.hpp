#pragma once
#include <iostream>
#include <SFML/Window.h>
#include <vector>
#include<SFML/Graphics.hpp>
#include<time.h>
#include<SFML/Window.hpp>
#include<SFML/Graphics.h>
//#include<Menu.h>
#include"Game.hpp"


class Game
{

public:
    virtual void start() = 0;
    Game();
    virtual ~Game();
};
