#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

class Game;

class Controller {
    Game *g;
public:
    Controller(); // idk if this does anything
    void startGame(char race, bool isTesting);
    bool playerAction(char dir1, char dir2, char actionType = 0);
    void restartGame(char race);
    void quitGame();
    void print();
};

#endif


// Controller(bool isTesting) : isTesting{isTesting}

// Controller::startGame()
// -> prompt user for race or QUIT
// -> make sure user inputted a valid race, if not re-prompt
// -> initial Game based on inputted player race + isTesting

// Controller::restartGame()
// -> delete g
// -> call Controller::startGame()

// Controller::quitGame()
// -> delete g

// Controller::print()
// -> call Game::printGame(), which prints g.td and additional information

// Controller::getIsFinished()
// -> returns Game::isFinished()

// Controller::playerAction(char dir1, char dir2, char actionType = 0)
// -> check valid direction:
    // -> if invalid, return false.
    // -> if valid, continue processing:
// -> if actionType == 'a':
    // -> g.attack(dir1, dir2)
// -> if actionType == 'u':
    // -> g.usePotion(dir1, dir2)
// else
    // -> g.move(dir1, dir2)
// -> return true;
