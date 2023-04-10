#ifndef _CELL_H_
#define _CELL_H_

#include <vector>

// enum FloorType {Blank, Wall, Tiles, Passage, Door};

// NOTE: consider every Cell owning a Position, and an Entity having a position.
// -> avoids the weird coupling between Cell and Entity, where both have a reference/pointer to each other


// enum FloorType {
//     Blank=0,
//     Wall,
//     Door,
//     Passage,
//     Tile,
//     Staircase,
//     PlayerPos,
//     EnemyPos,
//     ItemPos
// };


enum FloorType {
    Unknown=0,
    Blank,
    VerticalWall,
    HorizontalWall,
    Door,
    Passage,
    Tile
};

struct Position {
    int row, column;
};

class Entity;

class Cell{

    Position pos;
    int chamber = -1;
    char symbol;
    bool hasEntity;
    bool isStairCase = false;
    FloorType type;
    std::vector<Cell*> neighbours; // maybe don't need? otherwise, neighbours would be calculated every move at runtime
    Entity* e;

    public:
        // Constructor
        Cell(int row, int column, char symbol);

        // Setters
        void setFloorType(char symbol);
        void setEntity(Entity* e);
        void setNeighbours(std::vector<Cell*> neighbours);
        void setIsStairCase(bool isStairCase);
        void setChamber(int chamber);
        void setSymbol(char symbol);
        void setHasEntity(bool hasEntity);

        // Getters
        int getChamber() const;
        Position getPosition() const;
        char getSymbol() const;
        FloorType getType() const;
        std::vector<Cell*> getNeighbours() const;
        Entity* getEntity() const;
        bool getHasEntity() const;
        bool getIsStairCase() const;

        bool isNeighbour(Cell* other) const;
};

#endif
