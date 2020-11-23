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
    std::vector<Enemy>m_enemyArmy;

    unsigned int  m_coinsCount;

    int m_score;
    int m_totalScore;
    int m_maxScore;

    bool m_touchrope;
    Location findRope(int i);
    Location findLadder(char direction, int i);
    void setScore(char upOrDown);
    void setTotalScore(char upOrDown);
    bool handleRegularKey(int c);
    void buildNewLevel();
    void moveOnBoard();
    void handleSpecialKey();
    void gravity(int c);
    void gravityEnemy(int i);
    char nextStep(Location current, Location destention);
    Location moveToLadder();




    Location moveEnemy(int i);
    void setNewLevel();
    void setWinningScreen();
    void setMaxScore();
    void gameOver();
    void endGame();
    void setArmy();
    bool hitEnemy();
public:

    GameController();
    void play();
    bool isValidPlayer(Location objectToMove, std::vector<std::string> &currentMap, Location currentLocation);
    bool isValidEnemy(Location objectToMove, std::vector<std::string>& currentMap, Location currentLocation, int i);
};

