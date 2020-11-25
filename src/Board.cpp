#include "Board.h"

Board::Board(): m_size (0), m_currentLevel (0)
{
    //open the maps file.
    m_maps.open("Board.txt");
    //print error if unable to load file
    if (!m_maps.is_open()){
        std::cerr << "Cannot load level\n";
        exit(EXIT_FAILURE);
    }
    BuildLevel();
    setArmySize(getEnemyCount());
}



void Board::printBoard(Player player, std::vector<Enemy> enemy) 
{
    //for enemy's count
    auto enemys = 0;
    Screen::resetLocation();
    //set each enemy on board
    for (enemys = 0; enemys < getArmySize(); enemys++) 
    {
        m_level[enemy[enemys].getCurrentLocation().row][enemy[enemys].getCurrentLocation().col] = '%';
    }
    //set player on map
    m_level[player.getCurrentLocation().row][player.getCurrentLocation().col] = player.getShape();
    //print map
    for (int i = 0; i < m_size; i++)
        std::cout << m_level[i] << std::endl;
}

int Board::getBoundings() const
{
    return m_size;
}

int Board::getArmySize() const
{
    return m_armySize;
}

void Board::setArmySize(int size)
{
    m_armySize = size;
}

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
    //for row and col indexes
    unsigned int height_index=0,width_index=0;
    //to run on each row
    for (height_index = 0; height_index < m_size; height_index++) {
            //to run on each column
        for (width_index = 0; width_index < m_size; width_index++) {
            //set player's location and remove player from the board
            if (m_level[height_index][width_index] == '@') {
                m_level[height_index][width_index] = ' ';
                return Location(height_index, width_index);
            }
        }
    }
    return Location(0, 0);
}

void Board::setLevel1()
{
    m_currentLevel = 0;
}

int Board::getCurrLevel()const 
{
    return m_currentLevel;
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
    //for row and col indexes
    unsigned int height_index = 0, width_index = 0,coinsCounter=0;
    //to run on each row
    for (height_index = 0; height_index < m_size; height_index++) {
        //to run on each column
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
    return m_restartLevel[currentLocation.row][currentLocation.col];
}

void Board::BuildLevel() 
{
    m_size = 0;
    //get boundings from file
    m_maps >> m_size;
    //check if there are more maps
    if (m_size != 0)
    {
        m_currentLevel++;
    }
    m_maps.get();
    clearLevel();
    //run on each row and copy
    for (unsigned int i = 0; i < m_size; i++) 
    {
        //to get each line
        auto line = std::string();
        std::getline(m_maps, line);
        m_level.push_back(line);
    }
    setArmySize(getEnemyCount());
    m_restartLevel = m_level;
    m_score = 0;
    m_maxScore = getCoinsCount() * 2 * getCurrLevel();
}

void Board::clearLevel() 
{
    m_level.clear();
}

int Board::getEnemyCount()const
{
    //for row and col indexes
    unsigned int height_index = 0, width_index = 0,counter=0;
    //to run on each row
    for (height_index = 0; height_index < m_size; height_index++) 
    {
        //to run on each column
        for (width_index = 0; width_index < m_size; width_index++) 
        {
            if (m_level[height_index][width_index] == '%') {
                counter ++;
            }
        }
    }
    return counter;
}

Location Board::getEnemy() {
    //for row and col indexes
    unsigned int height_index = 0, width_index = 0;
    //to run on each row
    for (height_index = 0; height_index < m_size; height_index++) 
    {
        //to run on each column
        for (width_index = 0; width_index < m_size; width_index++) 
        {
            if (m_level[height_index][width_index] == '%')
            {
                m_level[height_index][width_index] = ' ';
                return Location(height_index,width_index);
            }

        }

    }
    return Location(0, 0);
}

bool Board::isNextSpace(Location location)const 
{
    if (m_level[location.row][location.col] == ' ') 
    {
        return 1;
    }
    return 0;
}

bool Board::isNextCoin(Location location) const
{
    if (m_level[location.row][location.col] == '*') 
    {
        return 1;
    }
    return 0;
}

bool Board::isNextOnRope(Location location)const 
{
    //to find if there is rope in current location
    auto ropeAbove = location.row - 1;

    if (ropeAbove < 0) 
    {
        return 0;
    }

    if (m_level[ropeAbove][location.col] == '-') 
    {
        return 1;
    }

    return 0;
}

bool Board::isNextOnLadder(Location location)const
{
    if (m_restartLevel[location.row][location.col] == 'H') 
    {
        return 1;
    }
    return 0;
}

bool Board::isNextEnemy(Location location)const 
{
    if (m_level[location.row][location.col] == '%') 
    {
        return 1;
    }
    return 0;
}

bool Board::isSpace(Location location)const 
{
    if (m_level[location.row][location.col] == ' ') 
    {
        return 1;
    }
    return 0;
}

int Board::getMaxScore()const
{
    return m_maxScore;
}

int Board::getCurScore()const 
{
    return m_score;
}

void Board::resetGame()
{
    m_maps.clear();
    m_maps.seekg(0);
}


Board::~Board()
{
    m_maps.close();
}
