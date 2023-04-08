#ifndef _ENTITY_H_
#define _ENTITY_H_

class Cell;

class Entity {
    Cell* c;
public:
    Entity();
    ~Entity();

    Cell getCell();

    void setCell(Cell *c);
    void swapCells(Cell *c);

    // what are there for?
    bool isPlayer();
    bool isEnemy();
    bool isItem();
};

#endif
