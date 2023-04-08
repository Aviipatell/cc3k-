#ifndef _CELL_H_
#define _CELL_H_

#include <vector>

// enum FloorType {Blank, Wall, Tiles, Passage, Door};

// NOTE: consider every Cell owning a Position, and an Entity having a position.
// -> avoids the weird coupling between Cell and Entity, where both have a reference/pointer to each other


enum FloorType {
    blank=0,
    wall,
    door,
    passage,
    tile,
    staircase,
    player,
    enemy,
    item
};

struct Position {
    int row, column;
};

class Entity;

class Cell{

    Position pos;
    int chamber = -1;
    char symbol;
    bool isStairCase = false;
    FloorType type;
    std::vector<Cell*> neighbours; // maybe don't need? otherwise, neighbours would be calculated every move at runtime
    Entity* e;

    public:

        Cell(int row, int column, char symbol); // parse symbol, set FloorType

        void setEntity(Entity* e);
        void setNeighbours();
        void setIsStairCase(bool b);
        void setChamber(int val);

        int getChamber() const;
        Position getPosition() const;
        char getSymbol() const;
        FloorType getType() const;
        std::vector<Cell*> getNeighbours();
        Entity* getEntity();
};

#endif
