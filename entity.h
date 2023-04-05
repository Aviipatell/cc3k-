#ifndef __ENTITY_H_
#define __ENTITY_H_

class Cell;

class Entity {
    Cell* c;
public:
    Entity();
    ~Entity();

    Cell getCell();

    void setCell(Cell *c);
    void swapCells(Cell *c);
    bool isPlayer();
    bool isEnemy();
    bool isItem();
};

#endif
