#pragma once

class GameSFMLSettings
{    
    int distanceBetweenFields;
    int distanceFromLeftEdge;
    int distanceFromTopEdge;
    int fieldSizeX;
    int fieldSizeY;

public:
    int getDistanceBetweenFields();
    int getDistanceFromLeftEdge();
    int getDistanceFromTopEdge();
    int getFieldSizeX();
    int getFieldSizeY();

    GameSFMLSettings();
    ~GameSFMLSettings();
};
