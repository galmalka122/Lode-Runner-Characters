#pragma once
#include "Location.h"
#include "Board.h"
class Player {

private:
    //location of player
    Location m_playerLocation;
    //for player shape
    char m_shape;
    //for life remaining
    int m_life;


public:
    Player();//constructor

    void setPlayer(Location location);//set player new location
    void setShape(char shape);//set player's shape
    void setLife(char plusMinus);//set player's life

    void playerClear();//delete players location

    Location getCurrentLocation()const;//get the player's location
    int getLife() const;//get the life count of the player
    char getShape()const;//get the current shape of player

    bool isOnRope(std::vector<std::string> level)const;//check if player is on rope
    bool isOnLadder(std::vector<std::string> level)const;//check if player is on laddder
    Location findLocation(int c, char destination);//find next or last location by user's key
    
};

