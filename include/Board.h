#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "io.h"
#include "windows.h"
#include "Location.h"
#include "Player.h"
#include "Enemy.h"
class Player;
class Enemy;
class Board {
private:
    std::vector<std::string> m_level;
    std::vector<std::string> m_restartLevel;
    std::ifstream m_maps;
    unsigned int m_size;
    unsigned int m_currentLevel;
    unsigned int m_maxScore;
    unsigned int m_score;
    unsigned int m_armySize;

   



public:
    Board(); //constructor of Board

    void setLevel1(); //set the first level after restarting game
    void resetGame(); //reset the game after loseing
    void setLevel(std::vector<std::string> newMap);
    void setLastLevel(std::vector<std::string> newMap);
    void BuildLevel();
    void clearLevel();
    bool isNextEnemy(Location location)const;
    void printBoard(Player player, std::vector<Enemy> enemy);

    std::vector<std::string> getLevel() const;
    std::vector<std::string> getLastLevel() const;
    Location getPlayer();
    Location getEnemy();
    char getCurrentChar(const Location currentLocation);
    int getCurrLevel()const;
    int getEnemyCount()const;
    int getCurScore()const;
    int getCoinsCount()const;
    int getMaxScore()const;
    int getBoundings() const;
    int getArmySize()const;
    void setArmySize(int size);
    bool isNextSpace(Location location)const;
    bool isNextCoin(Location location)const;
    bool isNextOnRope(Location location)const;
    bool isNextOnLadder(Location location)const;
    bool isSpace(Location location)const;
    ~Board(); //distructor of Board
};

