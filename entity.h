#ifndef _ENTITY_H_
#define _ENTITY_H_

class Cell;

class Entity {
    Cell* c;
public:
    virtual ~Entity() = 0; // make entity abstract

    Cell* getCell();
    void setCell(Cell *c);
    // void swapCell(Cell *c);
};

#endif
