#include "MousePositionConverter.hpp"
#include "catch.hpp"
#include "GameSFMLSettings.hpp"

MousePositionConverter::MousePositionConverter(MinesweeperBoard* board)
{
    GameSFMLSettings settings;
    distanceBetweenFields = settings.getDistanceBetweenFields();
    distanceFromLeftEdge = settings.getDistanceFromLeftEdge();
    distanceFromTopEdge = settings.getDistanceFromTopEdge();
    fieldSizeX = 20;
    fieldSizeY = 20;
    fieldCountX = board->getBoardWidth();
    fieldCountY = board->getBoardHeight();
}

sf::Vector2i MousePositionConverter::decodeMousePosition(int X, int Y)
{
    sf::Vector2i position;
    position.x = X;
    position.y = Y;
    int tab[2], counter, end;
    int x = 0, y = 0;
    for (tab[0] = distanceFromLeftEdge,
         tab[1] = fieldSizeX+distanceFromLeftEdge,
         counter = 0,
         end = fieldCountX*(fieldSizeX + distanceBetweenFields) - distanceBetweenFields + distanceFromLeftEdge;
            tab[1] <= end+1;
         ++counter)
    {
        if (position.x >= tab[0] and position.x <= tab[1]){
            x = counter;
            tab[1] = end+2;
        }
        else if (position.x > tab[1]){
        tab[0] = tab[1] + distanceBetweenFields;
        tab[1] = tab[0] + fieldSizeX;
        }
    }

    for (tab[0] = distanceFromTopEdge,
         tab[1] = fieldSizeY+distanceFromTopEdge,
         counter = 0,
         end = fieldCountY*(fieldSizeY + distanceBetweenFields) - distanceBetweenFields + distanceFromTopEdge;
            tab[1] <= end+1;
         ++counter)
    {
        if (position.y >= tab[0] and position.y <= tab[1]){
            y = counter;
            tab[1] = end+2;
        }
        else if (position.y > tab[1]){
        tab[0] = tab[1] + distanceBetweenFields;
        tab[1] = tab[0] + fieldSizeY;
        }
    }

    if (x >= 0 and y >= 0 and x <= fieldCountX and y <= fieldCountY)
    {
        position.x = x;
        position.y = y;
        return position;
    }
}

sf::Vector2i MousePositionConverter::codeFieldPosition(int X, int Y)
{
    sf::Vector2i position;
    int x, y;
    if (X == 0) x = distanceFromLeftEdge;
    if (Y == 0) y = distanceFromTopEdge;
    if (X > 0) x = distanceFromLeftEdge + X*fieldSizeX + X*distanceBetweenFields;
    if (Y > 0) y = distanceFromTopEdge + Y*fieldSizeY + Y*distanceBetweenFields;
    position.x = x;
    position.y = y;
    return position;
}
