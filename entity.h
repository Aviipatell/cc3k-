#ifndef _ENTITY_H_
#define _ENTITY_H_

class Cell;

class Entity {
    Cell* c;
public:
    Entity();
    virtual ~Entity() = 0; // make entity abstract

    Cell* getCell();
    void setCell(Cell *c);
    void swapCell(Cell *c);

    // what are these for?
    bool isPlayer();
    bool isEnemy();
    bool isItem();
};

#endif
