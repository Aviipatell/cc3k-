#ifndef __CELL_H_
#define __CELL_H_

#include "cell.h"
#include <vector>

enum FloorType{Blank, Wall, Tiles, Passage, Door};
class Entity;

class Cell{
    int row;
    int col;
    FloorType floor;
    int chamber;
    std::vector<Cell*> neighbours;
    Entity *e;

    public:
        int getRow();
        int getColumn();
        FloorType getType();
        int getChamber();
        std::vector<Cell*> getNeighbours();
        void setNeighbours();
        Entity* getEntity();
        void setEntity(Entity *e);

}
#endif

