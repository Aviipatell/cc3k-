#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <string>
#include <iostream>
#include <random>

#include "game.h"

class Controller {
    Game *g;
    GameMode mode;
    std::string floorPlanSrc;
    std::string msg;
    std::default_random_engine rng;
    public:
        Controller(bool isTesting, std::string floorPlanSrc, bool isSeeded, unsigned seed);
        ~Controller();
        void startGame();
        void restartGame();
        void quitGame();
        void printGame();

        Direction getValidDirection(char dir1, char dir2);
        bool playerAction(char dir1, char dir2, char actionType = 0);
        bool isGameOver();

        std::string getMsg();
        void setMsg(std::string msg="");
};

#endif
