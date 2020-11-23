#pragma once
#include "Location.h"
#include "Board.h"
class Enemy {

private:

    Location m_enemyLocation;
    char m_enemyShape;
    bool m_onLadder;
    bool m_onCoin;
    bool m_onRope;
    
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
    void setOnLadder(int On);
    bool getOnLadder()const;
    bool isOnRope(std::vector<std::string> level)const;
    bool isClimbing(std::vector<std::string> level)const;
    void setOnRope(int On);
    bool getOnRope()const;
};

