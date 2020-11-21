#pragma once
#include "Player.h"
#include "Board.h"
#include "Enemy.h"
#include "io.h"
#include <cstdlib>
const int KB_ESCAPE = 27;
class GameController {
private:

    Board m_level;
    Player m_player;
    Enemy m_enemy;

    unsigned int  m_coinsCount;

    int m_score;
    int m_totalScore;
    int m_maxScore;

    bool m_touchrope;

    void setScore(char upOrDown);
    void setTotalScore(char upOrDown);
    bool handleRegularKey(int c);
    void buildNewLevel();
    void moveOnBoard();
    void handleSpecialKey();
    void gravity(int c);
    char nextStep(Location current, Location destention);
    Location moveEnemy();
    void setNewLevel();
    void setWinningScreen();
    void setMaxScore();
    void gameOver();
public:

    GameController();
    void play();
    bool isValid(Location objectToMove, std::vector<std::string> &currentMap, Location currentLocation);
};

