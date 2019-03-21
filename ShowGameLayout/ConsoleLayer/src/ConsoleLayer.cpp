#include "ConsoleLayer.hpp"
#include <cstdlib>
#include <iostream>
#include "Operations.hpp"

ConsoleLayer::ConsoleLayer(GameManagement* Game)
{
    game = Game;
}

ConsoleLayer::~ConsoleLayer()
{
    delete game;
}

void ConsoleLayer::clrscr()
{
    system("clear");
}

std::string ConsoleLayer::getCharFromField(int X, int Y)
{
    switch (game->getFieldSign(X, Y))
    {
        case FieldStatus::BLOW_UP: return "X";
        case FieldStatus::BOMB: return "_";
        case FieldStatus::FLAG: return "?";
        case FieldStatus::HIDDEN:return "*";
        case FieldStatus::EMPTY: return " ";
        case FieldStatus::NUMBER: return std::to_string(game->getNOBN(X, Y));
        case FieldStatus::ERROR: debug::cerr("ERROR! Bad char return!");
    }
    return "ERROR! Bad char getter!";
}

std::string ConsoleLayer::prepareBoardToString()
{
    std::stringstream ss;

    for (int countY = 0; countY <= game->getSizeY(); ++countY)
    {
        if (countY == 0){
            ss << "  ";
            for (int i = 1; i <= game->getSizeX(); i++)
            {
                if (i < 10) ss << "  " << i;
                if (i > 10) ss << " " <<i;
                if (i == 10) ss << " " << i;
            }
            ss << std::endl;
        }
        else
        {
            for (int countX = 0; countX <= game->getSizeX(); ++countX){
                if (countX == 0 and countY <= 9) ss << countY << " ";
                if (countX == 0 and countY > 9) ss << countY;
                if (countX != 0) ss << "  " << getCharFromField(countX, countY);
                if (countX == game->getSizeX()) ss << std::endl;
            }
        }
    }
    return ss.str();
}

std::string ConsoleLayer::winScreen()
{
    std::stringstream ss;
    ss << "      Congratulacions!      " << std::endl <<
          "         You win!           " << std::endl;
    return ss.str();
}

std::string ConsoleLayer::looseScreen()
{
    std::stringstream ss;
    ss << "           Sorry!            " << std::endl <<
          "         You loose!          " << std::endl;
    return ss.str();
}

void ConsoleLayer::showOnScreen(ShowStatus choose)
{
    switch (choose)
    {
        case ShowStatus::WIN: std::cout << winScreen(); break;
        case ShowStatus::LOOSE: std::cout << looseScreen(); break;
        case ShowStatus::TABLE: std::cout << prepareBoardToString(); break;
        case ShowStatus::SHOW_BOARD : game->setAllFieldsNotHidden();; break;
        case ShowStatus::CLEAR: clrscr(); break;
        case ShowStatus::SCORES: std::cout << "You make: " << game->scores() << " flags right! " << std::endl; break;
    }
}

OperationOnField ConsoleLayer::getChooseFlagOrBomb()
{
    std::cout << "   Please write your choise:   " << std::endl;
    std::cout << "       1. Check Field          " << std::endl;
    std::cout << "       2. Make Flag            " << std::endl;
    std::cout << "       3. Delete Flag          " << std::endl;
    std::cout << "       0. EXIT                 " << std::endl;
    int number;
    std::cin >> number;

    switch (number)
    {
        case 1: return OperationOnField::CHECK_FIELD;
        case 2: return OperationOnField::MAKE_FLAG;
        case 3: return OperationOnField::DELETE_FLAG;
        case 0: exit(0);
    }
}

Vector2xy ConsoleLayer::getLocationFromUser()
{
    Vector2xy local;
    std::cout << "  Please write location (x,y): " << std::endl;
    std::cin >> local.x;
    std::cin >> local.y;
    return local;
}

void ConsoleLayer::start()
{
    while (game->checkGameStatus() == GameStatus::RUNNING)
    {
        showOnScreen(ShowStatus::CLEAR);
        showOnScreen(ShowStatus::TABLE);

        OperationOnField arg (getChooseFlagOrBomb());
        Vector2xy local = getLocationFromUser();

        switch (arg)
        {
            case OperationOnField::CHECK_FIELD:
                {
                    if (!game->checkAndSetField(local.x, local.y)){
                        showOnScreen(ShowStatus::LOOSE);
                        showOnScreen(ShowStatus::SCORES);
                        showOnScreen(ShowStatus::SHOW_BOARD);
                        showOnScreen(ShowStatus::TABLE);
                        exit(1);
                    }
                } break;
        case OperationOnField::MAKE_FLAG: game->makeFlag(local.x,local.y); break;
        case OperationOnField::DELETE_FLAG: game->removeFlag(local.x, local.y); break;
        }

        if (game->checkGameStatus() == GameStatus::FINISH_WIN)
        {
            showOnScreen(ShowStatus::WIN);
            showOnScreen(ShowStatus::SCORES);
            showOnScreen(ShowStatus::SHOW_BOARD);
            showOnScreen(ShowStatus::TABLE);
            exit(1);
        }
    }
}
