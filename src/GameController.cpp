#include "GameController.h"
//----------------------------------------------------------------------------
GameController::GameController():m_totalScore(0), m_score(0), m_maxScore(0),
                                            m_touchrope(0), m_coinsCount(0){
    //set player location
    m_player.setPlayer(m_level.getPlayer());
    //set map
    m_level.getLevel();
    //Get army of enemys
    setArmy();
    //Max score of level
    setMaxScore();
}
//----------------------------------------------------------------------------

void GameController::setArmy() {
    Enemy enemy;
    m_enemyArmy.clear();
    //finding enemys in the map, and insert them in to array of enemys
    for (int i = 0; i < m_level.getArmySize(); i++) {
        enemy.setEnemy(m_level.getEnemy());
        m_enemyArmy.push_back(enemy);
    }
}

void GameController::play(){

    //GAME LOOP
    for (auto exit = false; !exit;)
    {
     
        //player picked all coins
        if (m_score == m_maxScore) {

            setNewLevel();
            setMaxScore();
            setScore('L');

            //no more maps(player won the game)
            if (m_level.getBoundings() == 0) {

                setWinningScreen();
                std::exit(EXIT_SUCCESS);
            }
        }
        //if player hit enemy
        if (hitEnemy()) {

            //If player takes coin right before touching enemy
            if (m_maxScore != m_score) {
                endGame();
            }  
        }
        else {
            //Moving board next step After all objacts updated
            moveOnBoard();

            auto c = Keyboard::getch();

            switch (c)
            {
            case 0:
            case SPECIAL_KEY:
                handleSpecialKey();

                break;
            default:
                exit = handleRegularKey(c);
                break;
            }
        }
    }
}
//----------------------------------------------------------------------------
bool GameController::handleRegularKey(int c)
{
    switch (c)
    {
        case KB_ESCAPE:
            std::cout << "Escape pressed. Exiting...\n";
            return true;
        default:
            std::cout << "Unknown regular key pressed (code = " << c << ")\n";
            break;
    }

    return false;
}
//----------------------------------------------------------------------------
void GameController::handleSpecialKey()
{
    auto c = Keyboard::getch();
    
    auto location = m_player.getCurrentLocation(); //gets player location

    auto map = m_level.getLevel(); //gets current map
    switch (c)
    {
        case KB_UP:
            //Player Choose to move up
            if (isValidPlayer(m_player.findLocation(c, 'N'), map, location))
                return;
            m_level.setLevel(map);
            m_player.setPlayer(m_player.findLocation(c, 'N'));
            break;
        case KB_DOWN:
            //Player Choose to move down
            if (isValidPlayer(m_player.findLocation(c, 'N'), map, location))
                return;
            m_level.setLevel(map);
            m_player.setPlayer(m_player.findLocation(c, 'N'));
            break;
        case KB_LEFT:
            //Player Choose to move left
            if (isValidPlayer(m_player.findLocation(c, 'N'), map,location))
                return;
            m_level.setLevel(map);
            m_player.setPlayer(m_player.findLocation(c, 'N'));
            break;
        case KB_RIGHT:
            //Player Choose to move right
            if (isValidPlayer(m_player.findLocation(c, 'N'), map, location))
                return;
            m_level.setLevel(map);
            m_player.setPlayer(m_player.findLocation(c, 'N'));
            break;
        default:
            std::cout << "Unknown special key pressed (code = " << c << ")\n";
            break;
    }

    gravity(c); //Gravity of player

    for (int i = 0; i < m_enemyArmy.size(); i++) {
        //loop going on each enemy right movement
        auto dest = moveEnemy(i); //gets enemy position
        if (map[dest.row][dest.col] == '%') {
            //if enemy right now position is on 
            //other enemy, enemy is deleted.
            //(both go into same directions)
            m_enemyArmy.erase(m_enemyArmy.begin() + i);
            m_level.setArmySize(m_enemyArmy.size());
            ReturnLastChar(location, map);
        }
        if (i >= m_enemyArmy.size()) {
            //after we delete enemys, enemys size is changed.
            //in order to not get any array exceptions,
            //checks if index bigger the enemys size.
            break;
        }
        m_enemyArmy[i].setEnemy(dest);

        if (!m_enemyArmy[i].isClimbing(map)) {
            //if enemy is not climbing on ladder, we 
            //go in and turn of the flag
            m_enemyArmy[i].setOnLadder(0);
        }
            gravityEnemy(i); //Gravity for each enemy
    }
}
//----------------------------------------------------------------------------
bool GameController::isValidPlayer(Location destination, std::vector<std::string> &currentMap,Location currentLocation) {
    //if player next move is ladder or rope
    if (m_level.isNextOnLadder(destination) || m_level.isNextOnRope(destination)) {
        //if player char is not S and trying to climb
        if (m_player.getShape() == '@' && (destination.row < currentLocation.row)) {

            return 1;
        }

        //if player set to S(1 step before climbing modes)
        if (m_player.getShape() == 'S') {

            //if the next move is rope and current position is ladder
            if (m_level.isNextOnRope(destination) && m_level.getCurrentChar(m_player.getCurrentLocation()) == 'H') {
                currentMap[currentLocation.row][currentLocation.col] = 'H';
            }
            //if the next move is rope
            else if (m_level.isNextOnRope(destination))
                currentMap[currentLocation.row][currentLocation.col] = ' ';
            //if coming from ground to rope
            else if (m_level.isNextOnLadder(destination) && m_player.isOnRope(m_level.getLevel())) {
                currentMap[currentLocation.row][currentLocation.col] = ' ';
            }
            //if coming from ladder
            else
                currentMap[currentLocation.row][currentLocation.col] = 'H';

        }
        //if coming from floor
        else {

            //If we already on rope or ladder
            m_player.setShape('S');
            currentMap[currentLocation.row][currentLocation.col] = ' ';
        }

        //next step is to collect coin
        if (m_level.isNextCoin(destination)) {
            setScore('U');
            setTotalScore('A');
        }
        return 0;
    }

    //if on ladder or rope and next move is to space(all S modes)
    else if (m_player.getShape() == 'S' && (m_level.isNextSpace(destination) || m_level.isNextCoin(destination)
        || m_level.getLevel()[destination.row][destination.col] == '-')) {

        //next step is to collect coin
        if (m_level.isNextCoin(destination)) {
            setScore('U');
            setTotalScore('A');
        }
        //from rope to ground
        if (m_player.isOnRope(m_level.getLevel())) {
            //trying to go up when player is on rope (not valid movment) 
            if (nextStep(currentLocation, destination) == 'U') {
                return 1;
            }
            else if (m_level.getLevel()[destination.row][destination.col] == '-') {
                m_touchrope = 1;
                currentMap[currentLocation.row][currentLocation.col] = ' ';
            }
            else currentMap[currentLocation.row][currentLocation.col] = ' ';
        }

        else if (m_level.getLevel()[destination.row][destination.col] == '-') 
            m_touchrope = 1;
        

        //from ladder to ground
        else 
            currentMap[currentLocation.row][currentLocation.col] = 'H';
        

        m_player.setShape('@');
        return 0;
    }
    //if player hit the wall's
    else if (currentMap[destination.row][destination.col] == '#')

        return 1;
    //if player trys to climb where he cant
    else if (nextStep(currentLocation, destination) == 'U'){

        return 1;

    }
    //if player is trying to 
    else if (nextStep(currentLocation, destination) == 'U' && m_level.isNextSpace(destination)) {
        return 1;
    }

    else if (m_level.isNextEnemy(destination)) {
        endGame();
        return 1;
    }
    
    else if (m_level.getLevel()[destination.row][destination.col] == '-') {
        m_touchrope = 1;
        currentMap[currentLocation.row][currentLocation.col] = ' ';
        return 0;
    }

    if (m_level.isNextCoin(destination)) {
        setScore('U');
        setTotalScore('A');
    }

    currentMap[currentLocation.row][currentLocation.col] = ' ';
    
    return 0;

}
//----------------------------------------------------------------------------
void GameController::gravity(int c) {
    auto location = m_player.getCurrentLocation();
    auto map = m_level.getLevel();
    auto moveObjectPos = location.row + 1;
    auto backwardLadder = location.col;
    bool isRope = 0;

    if (m_player.getShape() != 'S' && !m_level.isNextOnLadder(Location(moveObjectPos, location.col))) {
        while (map[moveObjectPos][location.col] != '#'&& map[moveObjectPos][location.col] != 'H' &&
            !m_level.isNextOnRope(Location(location.row, location.col))) {
            if (m_player.isOnRope(m_level.getLevel())) {
                map[location.row][location.col] = '-';
                isRope = 1;
                break;
            }
            if (m_touchrope) {
                if (map[m_player.findLocation(c, 'L').row][m_player.findLocation(c, 'L').col] == 'S') {
                    if (map[m_player.findLocation(c, 'L').row - 1][m_player.findLocation(c, 'L').col] == '-') {
                        if (c == KB_RIGHT) {
                            backwardLadder--;
                        }
                        else
                            backwardLadder++;
                        map[location.row][backwardLadder] = ' ';
                    }
                    else {
                        if (c == KB_RIGHT) {
                            backwardLadder--;
                        }
                        else
                            backwardLadder++;
                        map[location.row][backwardLadder] = 'H';
                    }
                }
                //bug when jumping from rope to other rope
                else if (map[m_player.findLocation(c, 'L').row][m_player.findLocation(c, 'L').col] == '-') {
                    if (c == KB_RIGHT) {
                        backwardLadder--;
                    }
                    else
                        backwardLadder++;
                    map[location.row][backwardLadder] = '-';
                }
                map[location.row][location.col] = '-';
                m_touchrope = 0;
            }
            else {
                map[location.row][location.col] = ' ';
            }
            if (m_level.isNextCoin(Location(location.row + 1, location.col)))
            {
                setScore('U');
                setTotalScore('A');
            }
            m_level.setLevel(map);
            m_player.setPlayer(Location(location.row + 1, location.col));
            if (m_level.getLevel()[m_player.getCurrentLocation().row][m_player.getCurrentLocation().col] == '-') {
                m_touchrope = 1;
            }
            
            location.row++;
            moveObjectPos++;
            std::system("cls");
            moveOnBoard();
        }
        if (isRope) {
            map[location.row][location.col] = '-';
            m_player.setShape('S');
            m_level.setLevel(map);
            m_player.setPlayer(Location(location.row + 1, location.col));
            moveOnBoard();
        }
        if (m_player.isOnRope(m_level.getLevel())) {
            m_player.setShape('S');
        }

    }
}

void GameController::gravityEnemy(int i) {
    auto location = m_enemyArmy[i].getCurrentLocation();
    auto map = m_level.getLevel();
    auto moveObjectPos = location.row + 1;
    auto backwardLadder = location.col;
    bool isRope = 0;

    if (!m_enemyArmy[i].isClimbing(map) && !m_level.isNextOnLadder(Location(moveObjectPos, location.col))) {
        while (map[moveObjectPos][location.col] != '#' && map[moveObjectPos][location.col] != 'H' && 
            !m_level.isNextOnRope(Location(location.row, location.col))) {
            m_level.setLevel(map);
            m_enemyArmy[i].setEnemy(Location(location.row + 1, location.col));
            if (m_level.getLevel()[m_player.getCurrentLocation().row][m_player.getCurrentLocation().col] == '-') {
                m_touchrope = 1;
            }

            location.row++;
            moveObjectPos++;
            std::system("cls");
            moveOnBoard();
        }
        if (isRope) {
            map[location.row][location.col] = '-';
            m_player.setShape('S');
            m_level.setLevel(map);
            m_player.setPlayer(Location(location.row + 1, location.col));
            m_level.printBoard(m_player, m_enemyArmy);
        }
        if (m_player.isOnRope(m_level.getLevel())) {
            m_player.setShape('S');
        }

    }
    m_level.printBoard(m_player, m_enemyArmy);
}


//----------------------------------------------------------------------------
char GameController::nextStep(Location current, Location destention) {

    if (current.row > destention.row) 
        return 'U';

    else if(current.row < destention.row)
        return 'D';

    if (current.col > destention.col)
        return 'L';

    else if (current.col < destention.col)
        return 'R';
    
    return 'E';
}
//----------------------------------------------------------------------------
Location GameController::moveEnemy(int i) {
    auto map = m_level.getLevel();  //gets current map
    auto location = m_enemyArmy[i].getCurrentLocation(); //gets current Enemy location
    
    //Steps counters
    int enemyStepsToLadder=0, enemyStepsToRope = 0;
    
    //Destination's of enemy
    Location destLadder(0,0),destRope(0,0);

    //If player Beneath enemy
    if (m_player.getCurrentLocation().row < location.row ) {
        //finds location of close ladder
        destLadder = findLadder('U',i, enemyStepsToLadder);
        
        //If enemy is already on a ladder
        if (m_level.getCurrentChar(m_enemyArmy[i].getCurrentLocation()) == 'H') {

            //Going down on the ladder 
            if (m_enemyArmy[i].getOnLadder()) {
                ReturnLastChar(location, map);
                return Location(location.row - 1, location.col);
            }
            //Activate flag of enemy on Ladder then going down
            ReturnLastChar(location, map); //Return last char deleted
            m_enemyArmy[i].setOnLadder(1);
            return Location(location.row - 1, location.col);
        }
        //Checks validation of movement
        if (isValidEnemy(destLadder, map, location,i)) {
            return(location);
        }
        m_level.setLevel(map);
        return(destLadder);

    }
    else if (m_player.getCurrentLocation().row > location.row)
    {

        if (m_enemyArmy[i].isOnRope(map)) {
            ReturnLastChar(location, map);
            m_enemyArmy[i].setOnRope(0);
            return Location(location.row + 1, location.col);
        }
        if (m_level.getCurrentChar(Location(location.row + 1, location.col)) == 'H') {
            if (m_enemyArmy[i].getOnLadder()) {
                ReturnLastChar(location, map);
                return Location(location.row + 1, location.col);
            }
            ReturnLastChar(location, map);
            m_enemyArmy[i].setOnLadder(1);
            return Location(location.row + 1, location.col);
        }
        destLadder = findLadder('D', i, enemyStepsToLadder);
        destRope = findRope(i, enemyStepsToRope);
        if (destRope.col != 0 && destLadder.col != 0) {
            if (enemyStepsToRope < enemyStepsToLadder) {

                if (m_enemyArmy[i].isOnRope(map) ||
                    m_level.getCurrentChar(Location(location.row - 1, location.col)) == '-') {

                    ReturnLastChar(location, map);
                    m_enemyArmy[i].setOnRope(1);
                    return Location(location.row + 1, location.col);
                }
                if (isValidEnemy(destRope, map, location, i)) {
                    return(location);
                }
                m_level.setLevel(map);
                return(destRope);
            }

            if (isValidEnemy(destLadder, map, location, i)) {
                return(location);
            }
            m_level.setLevel(map);
            return(destLadder);
        }
    
           
    
        
        else if (destLadder.col == 0) {

            if (m_enemyArmy[i].isOnRope(map) ||
                m_level.getCurrentChar(Location(location.row - 1, location.col)) == '-') {

                ReturnLastChar(location, map);
                m_enemyArmy[i].setOnRope(1);
                return Location(location.row + 1, location.col);
            }
            if (isValidEnemy(destRope, map, location, i)) {
                return(location);
            }
            m_level.setLevel(map);
            return(destRope);
        }
        else {
            if (m_level.getCurrentChar(m_enemyArmy[i].getCurrentLocation()) == 'H') {
                if (m_enemyArmy[i].getOnLadder()) {
                    ReturnLastChar(location, map);
                    return Location(location.row + 1, location.col);
                }
                ReturnLastChar(location, map);
                m_enemyArmy[i].setOnLadder(1);
                return Location(location.row + 1, location.col);
            }
            if (m_level.getCurrentChar(Location(location.row + 1, location.col)) == 'H') {
                if (m_enemyArmy[i].getOnLadder()) {
                    ReturnLastChar(location, map);
                    return Location(location.row + 1, location.col);
                }
                ReturnLastChar(location, map);
                m_enemyArmy[i].setOnLadder(1);
                return Location(location.row + 1, location.col);
            }
            if (isValidEnemy(destLadder, map, location, i)) {
                return(location);
            }
            m_level.setLevel(map);
            return(destLadder);
        }
    }

    else if (m_player.getCurrentLocation().col < location.col) {

        if (isValidEnemy(Location(location.row, location.col - 1), map, location,i)) {
            return(location);
        }
        m_level.setLevel(map);
        return Location(location.row, location.col - 1);
    }
    else {

        if (isValidEnemy(Location(location.row, location.col + 1), map, location,i)) {
            return(location);
        }
        m_level.setLevel(map);
        return Location(location.row, location.col + 1);
    }
    return Location(location);
}


Location GameController::findLadder(char direction,int i,int &steps) {
    auto map = m_level.getLevel();
    auto location = m_enemyArmy[i].getCurrentLocation();
    int col = location.col,
        directionToMove = location.row;
    
    if (direction=='D') {
        directionToMove++;
    }

    if (m_player.getCurrentLocation().col < location.col) {
        while (map[location.row][col] != '#') {
            if (m_level.getCurrentChar(Location(directionToMove, col)) == 'H') {
                steps = location.col - col;
                return(Location(location.row, location.col-1));
            }
            
            col--;
        }
    }
    col = location.col;
    while (map[location.row][col] != '#') {
            if (m_level.getCurrentChar(Location(directionToMove, col)) == 'H') {
                steps = col - location.col;
                return(Location(location.row, location.col + 1));
            }
            col++;
        }
    col = location.col;
    while (map[location.row][col] != '#') {
        if (m_level.getCurrentChar(Location(directionToMove, col)) == 'H') {
            steps = location.col - col;
            return(Location(location.row, location.col-1));
        }
        col--;
    }

    return(Location(0, 0));
}


Location GameController::findRope( int i, int& steps) {
    auto map = m_level.getLevel();
    auto location = m_enemyArmy[i].getCurrentLocation();
    int col = location.col,
        directionToMove = location.row - 1;

    if (m_player.getCurrentLocation().col < location.col) {
        while (map[location.row][col] != '#') {
            if (m_level.getCurrentChar(Location(directionToMove, col)) == '-') {
                steps = location.col - col;
                return(Location(location.row, location.col - 1));
            }
            col--;
        }
    }
    col = location.col;
    while (map[location.row][col] != '#') {
        if (m_level.getCurrentChar(Location(directionToMove, col)) == '-') {
            steps = col - location.col;
            return(Location(location.row, location.col + 1));
        }
        col++;
    }
    col = location.col;
    while (map[location.row][col] != '#') {
        if (m_level.getCurrentChar(Location(directionToMove, col)) == '-') {
            steps = location.col - col;
            return(Location(location.row, location.col - 1));
        }
        col--;
    }

    return(Location(0,0));
}

bool GameController::isValidEnemy(Location destination,
                                std::vector<std::string>& currentMap,
                                Location currentLocation
                                ,int i) {


    if (currentMap[destination.row][destination.col] == '#')
            return 1;
        
        //if Enemy trys to climb where he cant
    else if (nextStep(currentLocation, destination) == 'U' && m_level.isNextSpace(destination)) 
            return 1;
 
    else if (m_level.isNextCoin(destination)) {
        m_enemyArmy[i].setCoin(1);
    }
    else if (m_enemyArmy[i].getOnCoin()) {
        currentMap[currentLocation.row][currentLocation.col] = '*';
        m_enemyArmy[i].setCoin(0);
        return 0;
    }
    else if (m_level.isNextOnLadder(destination)) {
        if (m_enemyArmy[i].isClimbing(m_level.getLastLevel())) {
            currentMap[currentLocation.row][currentLocation.col] = 'H';
        }
        else if (m_enemyArmy[i].isOnRope(currentMap)) {
            currentMap[destination.row-1][currentLocation.col] = '-';
        }
        currentMap[destination.row][currentLocation.col] = ' ';
        m_enemyArmy[i].setOnLadder(1);
        return 0;
    }
    else if (m_enemyArmy[i].isClimbing(m_level.getLastLevel())) {
        if (currentMap[destination.row][destination.col] == '%') {
            currentMap[currentLocation.row][currentLocation.col] = m_level.getCurrentChar(currentLocation);
        }
            currentMap[currentLocation.row][currentLocation.col] = 'H';
            return 0;
    }
    else if (m_player.getCurrentLocation().col == m_enemyArmy[i].getCurrentLocation().col &&
             m_player.getCurrentLocation().row == m_enemyArmy[i].getCurrentLocation().row) {
             endGame();
    }
    currentMap[currentLocation.row][currentLocation.col] = ' ';

    return 0;



    //if player next move is ladder or rope
    

}

//----------------------------------------------------------------------------
void GameController::setNewLevel() {

    m_totalScore += (50 * m_level.getCurrLevel());
    std::system("cls");
    m_level.clearLevel();
    m_level.BuildLevel();
    //while for more enemys
    m_level.setLevel(m_level.getLevel());
    m_player.setShape('@');
    m_enemyArmy.clear();
    setArmy();
    setMaxScore();
    m_player.playerClear();
    m_player.setPlayer(m_level.getPlayer());

}
//---------------------------------------------------------------------------- 
void GameController::setWinningScreen() {

    std::system("cls");
    Screen::resetLocation();
    std::cout << "YOU WIN! YOUR SCORE IS " << m_totalScore << std::endl;
    Keyboard::getch();

}
//----------------------------------------------------------------------------
/*
*refreshing screen and prints after movement
*/
void GameController::moveOnBoard() {

    Screen::resetLocation();
    m_level.printBoard(m_player, m_enemyArmy);
    std::cout << "LIFE: " << m_player.getLife()+1 << std::endl
        << "SCORE: " << m_totalScore << std::endl
        << "LEVEL " << m_level.getCurrLevel()<<std::endl;

}
//----------------------------------------------------------------------------
/*
*adds or substract points to the score
*/
void GameController::setScore(char upOrDown) {

    if (upOrDown == 'U')

        m_score += (2 * m_level.getCurrLevel());

    else if (upOrDown == 'D')

        m_score -= (2 * m_level.getCurrLevel());

    else if (upOrDown == 'L')

        m_score =0;
}
//----------------------------------------------------------------------------
/*
*adds or substract points to the total score
*/
void GameController::setTotalScore(char addOrDecrease) {

    if (addOrDecrease == 'A')

        m_totalScore += (2 * m_level.getCurrLevel());

    else if (addOrDecrease == 'D')

        m_totalScore -= (2 * m_level.getCurrLevel());
    //decrease current score(L for lost)
    else if (addOrDecrease == 'L')

        m_totalScore -= m_score;
    //decrease all points(E for everything)
    else if (addOrDecrease == 'E')
        m_totalScore = 0;
}
//----------------------------------------------------------------------------
void GameController::setMaxScore() {

    m_maxScore = 2 * m_level.getCoinsCount() * m_level.getCurrLevel();

}
void GameController::gameOver()
{
    system("cls");
    Screen::resetLocation();
    std::cout << "GAME OVER!\nPress Enter to restart game.";
    m_level.clearLevel();
    m_enemyArmy.clear();
    m_player.playerClear();
    m_totalScore = 0;
    m_level.resetGame();
    getchar();

}
//----------------------------------------------------------------------------
void GameController::endGame() {
    if (m_player.getLife() == 0) {
        gameOver();
        setTotalScore('E');
        setScore('L');
        m_level.setLevel1();
        setNewLevel();
        m_player.setLife('F');
        setMaxScore();
    }
    else {
        m_level.clearLevel();
        m_player.setLife('M');
        setTotalScore('L');
        setScore('L');
        m_enemyArmy.clear();
        m_player.playerClear();
        m_player.setShape('@');
        m_level.setLastLevel(m_level.getLastLevel());
        m_player.setPlayer(m_level.getPlayer());
        m_level.setArmySize(m_level.getEnemyCount());
        setArmy();
    }
}
bool GameController::hitEnemy() {
    for (int i = 0; i < m_level.getArmySize(); i++) {
        if (m_player.getCurrentLocation().row == m_enemyArmy[i].getCurrentLocation().row &&
            m_player.getCurrentLocation().col == m_enemyArmy[i].getCurrentLocation().col) {
            return 1;
        }
    }
    return 0;
}

void GameController::ReturnLastChar(Location location, std::vector<std::string>& map) {
    map[location.row][location.col] = m_level.getCurrentChar(location);
    m_level.setLevel(map);
}