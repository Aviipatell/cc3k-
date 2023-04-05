#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "string"

class Game;

class Controller {
    Game *g;
    bool isTesting;
    std::string floorPlanSrc;
    std::string msg;
    public:
        Controller(bool isTesting, std::string floorPlanSrc);
        void startGame();
        void restartGame();
        void quitGame();
        void printGame();

        bool playerAction(char dir1, char dir2, char actionType = 0);
        bool isGameOver();

        std::string getMsg();
};

#endif

// ***** FIELDS ****

// -> probably add isTesting and floorPlanSrc here to clean up main a bit.
// -> as a result, Controller constructor will be passed in those two values

 // **** METHODS ****

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

// Controller::printGame()
// -> call Game::printGame(), which prints g.td and additional information

// Controller::isGameOver()
// -> returns Game::getIsOver()

// Controller::playerAction(char dir1, char dir2, char actionType = 0)
// -> check valid direction:
    // -> if invalid, return false.
    // -> if valid, continue processing:
// -> if actionType == 'a':
    // -> g.attack(dir1, dir2)
// -> if actionType == 'u':
    // -> g.usePotion(dir1, dir2)
// else
    // -> g.movePlayer(dir1, dir2)
// -> return true;
