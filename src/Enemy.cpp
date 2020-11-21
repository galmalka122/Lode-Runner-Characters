#include "..\include\Player.h"
#include "Board.h"
#include "Enemy.h"

Enemy::Enemy() : m_enemyLocation(Location(0, 0)) {}

void Enemy::setEnemy(Location location) {

	m_enemyLocation = location;

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
