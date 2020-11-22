#pragma once
#include "Location.h"
#include "Board.h"
class Enemy {

private:

    Location m_enemyLocation;
    char m_enemyShape;
    bool m_onLadder;
    bool m_onCoin;
    
public:
    Enemy();
    bool isOnLadder(std::vector<std::string> level)const;
    void setEnemy(Location location);
    Location getCurrentLocation()const;
    bool isValidMove()const;
    void enemyClear();
    void setShape(char shape);
    void setCoin(int On);
    bool getOnCoin();
    bool isOnRope(std::vector<std::string> level)const;
    void setOnLadder(int On);
    bool getOnLadder();
    bool isClimbing(std::vector<std::string> level)const;
};

