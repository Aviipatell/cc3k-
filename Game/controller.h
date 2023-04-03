#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

class Game;

class Controller {
    Game *g;
public:
    void startGame(char race);
    void restartGame(char race);
    void quitGame();
    void print();
};

#endif
