#include"GameSFMLSettings.hpp"

GameSFMLSettings::GameSFMLSettings()
{
    distanceBetweenFields = 10;
    distanceFromLeftEdge = 10;
    distanceFromTopEdge = 10+50;
    fieldSizeX = 20;
    fieldSizeY = 20;
}

GameSFMLSettings::~GameSFMLSettings()
{}

int GameSFMLSettings::getDistanceBetweenFields()
{
    return distanceBetweenFields;
}
int GameSFMLSettings::getDistanceFromLeftEdge()
{
    return distanceFromLeftEdge;
}
int GameSFMLSettings::getDistanceFromTopEdge()
{
    return distanceFromTopEdge;
}
int GameSFMLSettings::getFieldSizeX()
{
    return fieldSizeX;
}
int GameSFMLSettings::getFieldSizeY()
{
    return fieldSizeY;
}
