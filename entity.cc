#include "entity.h"
#include "cell.h"

Cell* Entity::getCell() {
    return this->c;
}

void Entity::setCell(Cell *c) {
    this->c = c;
}

void Entity::swapCell(Cell *c) {
    
}
