#pragma once
#include "Location.h"
#include "Board.h"
class Enemy {

private:

    Location m_enemyLocation;
    
public:
    Enemy();
    void setEnemy(Location location);
    Location getCurrentLocation()const;
    bool isValidMove()const;
    void enemyClear();
};

