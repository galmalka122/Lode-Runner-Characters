#include "Board.h"

Board::Board(): m_size (0), m_currentLevel (0){

    m_maps.open("Board.txt");
    if (!m_maps.is_open()){
        std::cerr << "Cannot load level\n";
        exit(EXIT_FAILURE);
    }
    BuildLevel();
}

void Board::printBoard(Player player,Enemy enemy) {
    
    system("cls");
    Screen::resetLocation();
    for (unsigned int i = 0; i < m_size; i++) {
        if (i == player.getCurrentLocation().row)
            m_level[i][player.getCurrentLocation().col] = player.getShape();
<<<<<<< HEAD
        if (i == enemy.getCurrentLocation().row)
=======
        if (i == enemy.getCurrentLocation().row && i != 0)
>>>>>>> gal
            m_level[i][enemy.getCurrentLocation().col] = '%';
        std::cout << m_level[i] << std::endl;
    }
}
int Board::getBoundings() const
{
    return m_size;
}
<<<<<<< HEAD
std::vector<std::string> Board::getLevel() const {
    return m_level;
}
std::vector<std::string> Board::getLastLevel() const {
    return m_restartLevel;
}

Location Board::getPlayer() {
=======
std::vector<std::string> Board::getLevel() const 
{
    return m_level;
}
std::vector<std::string> Board::getLastLevel() const 
{
    return m_restartLevel;
}

Location Board::getPlayer()
{
>>>>>>> gal
    unsigned int height_index=0,width_index=0;
    for (height_index = 0; height_index < m_size; height_index++) {
        
        /*size_t found;
        found = m_level[height_index].find("@");
        if(found != std::string::npos)
        }*/

            for(width_index=0;width_index<m_size;width_index++){
                    if (m_level[height_index][width_index] == '@'){
                        m_level[height_index][width_index] = ' ';
                        return Location( height_index, width_index);
                    }

            }

    }
    return Location(0, 0);
}

void Board::setLevel1(){

    m_currentLevel = 0;
}

<<<<<<< HEAD
void Board::setLastLevel(std::vector<std::string> newMap) {

    m_score = 0;
    m_level = newMap;

=======
int Board::getCurrLevel()const 
{
    return m_currentLevel;
>>>>>>> gal
}

void Board::setLastLevel(std::vector<std::string> newMap) 
{
    m_score = 0;
    m_level = newMap;
}

void Board::setLevel(std::vector<std::string> newMap) 
{
    m_level = newMap;
}

int Board::getCoinsCount() const
{
<<<<<<< HEAD

=======
>>>>>>> gal
    unsigned int height_index = 0, width_index = 0,coinsCounter=0;

    for (height_index = 0; height_index < m_size; height_index++) {

        for (width_index = 0; width_index < m_size; width_index++) {
            if (m_level[height_index][width_index] == '*') {
                coinsCounter++;
            }

        }

    }
    return coinsCounter;
}
char Board::getCurrentChar(const Location currentLocation) 
{
    return m_level[currentLocation.row][currentLocation.col];
}


void Board::BuildLevel() 
{
    m_size = 0;
    
    m_maps >> m_size;
    if (m_size != 0) {
        m_currentLevel++;
    }
    m_maps.get();
<<<<<<< HEAD
    resetLevel();
=======
    clearLevel();
>>>>>>> gal
    for (unsigned int i = 0; i < m_size; i++) {

        auto line = std::string();
        std::getline(m_maps, line);
        m_level.push_back(line);
    }
    m_restartLevel = m_level;
    m_score = 0;
    m_maxScore = getCoinsCount() * 2 * getCurrLevel();
}

void Board::clearLevel() 
{
    m_level.clear();
}

int Board::getEnemyCount() const
{
    

    unsigned int height_index = 0, width_index = 0,counter=0;
    for (height_index = 0; height_index < m_size; height_index++) {

        for (width_index = 0; width_index < m_size; width_index++) {

            if (m_level[height_index][width_index] == '%') {
                counter ++;
            }
        }
    }
    return counter;
}

Location Board::getEnemy() {

    unsigned int height_index = 0, width_index = 0,curCounter = getEnemyCount();
    for (height_index = 0; height_index < m_size; height_index++) {

        for (width_index = 0; width_index < m_size; width_index++) {
            if (m_level[height_index][width_index] == '%') {
                m_level[height_index][width_index] = ' ';
                curCounter --;
                if (curCounter == 0)
                    return Location(height_index,width_index);
            }

        }

    }
    return Location(0, 0);
}

bool Board::isNextSpace(Location location)const {

    if (m_level[location.row][location.col] == ' ') {
        return 1;
    }
    return 0;
}

bool Board::isNextCoin(Location location) const{
    if (m_level[location.row][location.col] == '*') {
        return 1;
    }
    return 0;
}

bool Board::isNextOnRope(Location location)const {

    auto ropeAbove = location.row - 1;
    if (m_level[ropeAbove][location.col] == '-') {
        return 1;
    }
    return 0;
}

bool Board::isNextOnLadder(Location location)const {

    if (m_level[location.row][location.col] == 'H') {
        return 1;
    }
    return 0;
}

bool Board::isSpace(Location location)const {

    if (m_level[location.row][location.col] == ' ') {
        return 1;
    }
    return 0;
}
int Board::getMaxScore()const {

    return m_maxScore;
}
int Board::getCurScore()const {

    return m_score;
}
<<<<<<< HEAD
=======
void Board::resetGame()
{
    m_maps.clear();
    m_maps.seekg(0);

}
>>>>>>> gal
void Board::setScore() {

    m_score += (2 * getCurrLevel());
}   
