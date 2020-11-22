#include "..\include\Player.h"
#include "Board.h"
#include "Enemy.h"

Enemy::Enemy() : m_enemyLocation(Location(0, 0)), m_enemyShape('%'), m_onLadder(0)
                , m_onCoin(0){}

void Enemy::setEnemy(Location location) {

	m_enemyLocation = location;

}

void Enemy::setShape(char shape) {

	m_enemyShape = '%';

}

Location Enemy::getCurrentLocation()const {

	return m_enemyLocation;
}

bool Enemy::isValidMove()const {


	return 0;
}

void Enemy::enemyClear()
{
	m_enemyLocation= Location(0, 0);
}

bool Enemy::isOnLadder(std::vector<std::string> level)const {
    int up = m_enemyLocation.row - 1, down = m_enemyLocation.row + 1;

    if (level[up][m_enemyLocation.col] == 'H' ||
        level[down][m_enemyLocation.col] == 'H') {
        return 1;
    }
    return 0;
}

bool Enemy::isClimbing(std::vector<std::string> level)const {
    if (level[m_enemyLocation.row][m_enemyLocation.col] == 'H') {
        return 1;
    }
    return 0;

}

bool Enemy::isOnRope(std::vector<std::string> level)const {
    int up = m_enemyLocation.row - 1;

    if (level[up][m_enemyLocation.col] == '-') {
        return 1;
    }
    return 0;
}
void Enemy::setOnLadder(int On) {
    m_onLadder = On;
}


void Enemy::setCoin(int On){
    m_onCoin = On;
}

bool Enemy::getOnCoin() {
    return m_onCoin;
}

bool Enemy::getOnLadder() {
    return  m_onLadder;
}