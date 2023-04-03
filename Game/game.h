#ifndef __GAME_H_
#define __GAME_H_

#include "controller.h"
#include <vector>

enum Direction {
    no,
    so,
    ea,
    we,
    ne,
    nw,
    se,
    sw
};

class Player;
class Cell;
class Item;
class Cell;
class Enemy;

class Game: public Controller {
    Player *p;
    std::vector<std::vector<Cell *>> floor;
    int level;
    std::vector<Item *> items;
    std::vector<Enemy *> enemies;
    TextDisplay *td;
public:
    void generateFloor(Player *p);
    void printGame();
    bool isValidCell(Direction dir);
};

#endif
