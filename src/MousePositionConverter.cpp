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
    int x0 = distanceFromLeftEdge;
    int y0 = distanceFromTopEdge;

    sf::Vector2i position;
    position.x = (X - x0) / (fieldSizeX + distanceBetweenFields);
    position.y = (Y - y0) / (fieldSizeY + distanceBetweenFields);

    return position;
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
