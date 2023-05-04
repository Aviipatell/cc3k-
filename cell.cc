#include "cell.h"
#include <iostream>

#include "entity.h"
// Constructor

Cell::Cell(int row, int column, char symbol) : pos{Position{.row = row, .column = column}}, symbol{symbol} {
    setFloorType(this->symbol);
}

// Setters

void Cell::setFloorType(char symbol) {
    FloorType type;
    switch(symbol) {
        case ' ':
            type = FloorType::Blank;
            break;
        case '|':
            type = FloorType::VerticalWall;
        case '-':
            type = FloorType::HorizontalWall;
            break;
        case '+':
            type = FloorType::Door;
            break;
        case '#':
            type = FloorType::Passage;
            break;
        case '.':
            type = FloorType::Tile;
            break;
        case '/':
            type = FloorType::Tile;
            isStairCase = true;
            break;
        default:
            type = FloorType::Unknown;
            break;
    }
    if (type == FloorType::Unknown) {
        this->hasEntity = true;
        this->type = FloorType::Tile;
    } else {
        this->hasEntity = false;
        this->type = type;
    }
}

void Cell::setHasEntity(bool hasEntity) {
    this->hasEntity = hasEntity;
}

void Cell::setEntity(Entity* e) {
    this->e = e;
    if (e == nullptr) {
        if (type == FloorType::Blank) {
            setSymbol(' ');
        } else if (type == FloorType::VerticalWall) {
            setSymbol('|');
        } else if (type == FloorType::HorizontalWall) {
            setSymbol('-');
        } else if (type == FloorType::Door) {
            setSymbol('+');
        } else if (type == FloorType::Passage) {
            setSymbol('#');
        } else {
            setSymbol('.');
        }
        setHasEntity(false);
    } else {
        std::cout << "enemy set entity called" << std::endl;
        setSymbol(e->getSymbol());
        setHasEntity(true);
    }
}

void Cell::setSymbol(char symbol) {
    this->symbol = symbol;
}

void Cell::setNeighbours(std::vector<Cell*> neighbours) {
    this->neighbours = neighbours;
}

void Cell::setIsStairCase(bool isStairCase) {
    this->isStairCase = isStairCase;
}

void Cell::setChamber(int chamber) {
    this->chamber = chamber;
}

// Getters

int Cell::getChamber() const {
    return this->chamber;
}

Position Cell::getPosition() const {
    return this->pos;
}

char Cell::getSymbol() const {
    return this->symbol;
}

FloorType Cell::getType() const {
    return this->type;
}

std::vector<Cell*> Cell::getNeighbours() const {
    return this->neighbours;
}

Entity* Cell::getEntity() const {
    return this->e;
}

bool Cell::getHasEntity() const {
    return this->hasEntity;
}

bool Cell::getIsStairCase() const {
    return this->isStairCase;
}

bool Cell::isNeighbour(Cell* other) const {
    for (Cell* c : this->neighbours) {
        if (c == other) return true;
    }
    return false;
}
