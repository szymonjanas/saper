#include <iostream>
#include <SFML/Window.h>
#include <vector>
#include<SFML/Graphics.hpp>
#include<time.h>
#include<SFML/Window.hpp>
#include<SFML/Graphics.h>
#include "Menu.hpp"
#include "ConsoleLayer.hpp"
#include"GraphicLayer.hpp"
#include"Game.hpp"

using namespace sf;
using namespace std;

int main()
{
    cout << "WELCOME IN SAPER" << endl;
    cout << "What kind of view do you prefer?" << endl;
    cout << "1. Console" << endl;
    cout << "2. Graphic" << endl;
    cout << "0. EXIT" << endl;
    int check = 0;
    bool checker = true;
    do
    {
        cin >> check;
        if (check >= 0 or check < 3) checker = false;
    } while (checker);

    Menu menu;
    if (check == 1)
    {
        menu.turnOnGame(Layer::CONSOLE);
    }
    if (check == 2)
    {
        menu.turnOnGame(Layer::GRAPHIC);
    }
    if (check == 0) exit(1);
}
