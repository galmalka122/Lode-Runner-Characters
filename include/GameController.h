#pragma once
#include "Player.h"
#include "Board.h"
#include "Enemy.h"
#include "io.h"

const int KB_ESCAPE = 27;
class GameController {
private:

    Board m_level; //open level
    Player m_player; //open a player
    std::vector<Enemy>m_enemyArmy; //gets 

    unsigned int  m_coinsCount; //counting coins

    int m_score; //score current level
    int m_totalScore; //total score of the game
    int m_maxScore; //max score for each level
    
    bool m_touchrope; //if some one touch rope

    Location findRope(int i, int& steps); //finding path to rope 

    Location findLadder(char direction, int i,int& steps); //finding path to ladder

    void addScore(char upOrDown); //setting score
    void setTotalScore(char upOrDown); //setting total score
    void setNewLevel(); //setting new level after finish level
    void setWinningScreen(); //if player win we set a winning screen
    void setMaxScore(); //set max score for each level
    void setArmy(); //setting army of enemies in level

    //handel user entered keys
    bool handleRegularKey(int c); 
    void handleSpecialKey();

    void moveOnBoard(); //moving next step on board

     

    void gravity(int c); //setting gravity on the player
    void gravityEnemy(int i); //setting gravity on the enemys
    
    char nextStep(Location current, Location destention); //finds the next step

    Location moveEnemy(int i); // finding enemy best movement

    

    
    
    void gameOver(); //end game after losing all life's
    void endGame(); //if enemy cought the player ending the round
    
    bool hitEnemy(); // checks if player hit enemy

    //finds the last character from the level map before all movements
    void ReturnLastChar(Location location, std::vector<std::string>& currentMap);
    
    //check movement validation of player
    bool isValidPlayer
        (Location objectToMove, std::vector<std::string>& currentMap, Location currentLocation);
    
    //check movement validation of enemies
    bool isValidEnemy
        (Location objectToMove, std::vector<std::string>& currentMap, Location currentLocation, int i);
    bool enemyHitEnemy(std::vector<std::string> map, Location dest, int currenemy);


public:

    GameController(); //builds the game
    void play(); // game loop
    
};

