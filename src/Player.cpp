#include "..\include\Player.h"
#include "Board.h"
#include "Player.h"

Player::Player() : m_playerLocation (Location(0,0)), m_shape('@'), m_life(2){}

void Player::setPlayer(Location location) {

	m_playerLocation = location;
}

Location Player::getCurrentLocation()const {
	return m_playerLocation;
}

void Player::setShape(char shape) {

	m_shape = shape;

}
char Player::getShape()const {
	return m_shape;
}

Location Player::findLocation(int c, char destination) {
    //to find last location
    if (destination == 'L') {
        if (c == KB_RIGHT)
            return (Location(m_playerLocation.row, m_playerLocation.col - 1));

        else if (c == KB_LEFT)
            return (Location(m_playerLocation.row, m_playerLocation.col + 1));

        else if (c == KB_UP)
            return (Location(m_playerLocation.row + 1, m_playerLocation.col));

        else if (c == KB_DOWN)
            return (Location(m_playerLocation.row - 1, m_playerLocation.col));
    }
    //to find next location
    if (destination == 'N') {
        if (c == KB_RIGHT)

            return (Location(m_playerLocation.row, m_playerLocation.col + 1));

        else if (c == KB_LEFT)
            return (Location(m_playerLocation.row, m_playerLocation.col - 1));

        else if (c == KB_UP)
            return (Location(m_playerLocation.row - 1, m_playerLocation.col));

        else if (c == KB_DOWN)
            return (Location(m_playerLocation.row + 1, m_playerLocation.col));
    }
    return Location(0, 0);
}

bool Player::isOnRope(std::vector<std::string> level)const {
    int up = m_playerLocation.row - 1;
    if (level[up][m_playerLocation.col] == '-') {
        return 1;
    }
    return 0;
}

bool Player::isOnLadder(std::vector<std::string> level)const {
    int up = m_playerLocation.row - 1, down = m_playerLocation.row + 1;

    if (getShape() == 'S' && (level[up][m_playerLocation.col] == 'H' ||
        level[down][m_playerLocation.col] == 'H')) {
        return 1;
    }
    return 0;
}

void Player::setLife(char plusMinus) {
    
    if (plusMinus == 'P') {
        m_life++;
    }

    if (plusMinus == 'M') {
        m_life--;
    }
    //f for full
    if (plusMinus == 'F')
        m_life = 2;
}
int Player::getLife() const 
{
    return m_life;
}
void Player::playerClear()
{
    m_playerLocation = Location(0, 0);
}