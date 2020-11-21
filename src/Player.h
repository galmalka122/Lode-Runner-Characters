#pragma once
#include "Location.h"
#include "Board.h"
class Player {

private:
    Location m_playerLocation;
    char m_shape;
    int m_life;


public:
    Player();
    void setPlayer(Location location);
    void playerClear();
    Location getCurrentLocation()const;
    Location findLocation(int c, char destination);
    void setShape(char shape);
    char getShape()const;
    bool isOnRope(std::vector<std::string> level)const;
    bool isOnLadder(std::vector<std::string> level)const;
    void setLife(char plusMinus);
    int getLife() const;
};

