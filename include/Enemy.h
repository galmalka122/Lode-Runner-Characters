#pragma once
#include "Location.h"
#include "Board.h"
class Enemy {

private:
    //to hold enemy's location
    Location m_enemyLocation;
    //for enemy's shape.
    char m_enemyShape;
    //to flag if enemy is on ladder
    bool m_onLadder;
    //to flag if enemy is on coin
    bool m_onCoin;
    //to flag if enemy is on rope
    bool m_onRope;
    
public:

    Enemy();//constructor

    Location getCurrentLocation()const;//get enemy's current location
    bool getOnCoin();//check if enemy is on coin
    bool getOnLadder()const;//check if enemy is on ladder
    bool getOnRope()const;//check if enemy is on rope

    void setEnemy(Location location);//set enemy's location
    void setShape(char shape);//set enemy's shape
    void setCoin(int On);//set onCoin flag
    void setOnLadder(int On);//set onladder flag
    void setOnRope(int On);//set onRope falg

    bool isOnRope(std::vector<std::string> level)const;//check if enmy is on rope
    bool isClimbing(std::vector<std::string> level)const;//check if enmy is currently climbing
    bool isOnLadder(std::vector<std::string> level)const;//check if enmy is on ladder
    void enemyClear();//clear enemy's location
   
};

