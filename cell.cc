#include "cell.h"

// Constructor

Cell::Cell(int row, int column, char symbol) : pos{Position{.row = row, .column = column}}, symbol{symbol} {
    setFloorType(this->symbol);
}

// Setters

void Cell::setFloorType(char symbol) {
    type = FloorType::Tile; // Maybe set to FloorType::Blank
    switch(symbol) {
        case ' ':
            type = FloorType::Blank;
            break;
        case '|':
        case '-':
            type = FloorType::Wall;
            break;
        case '+':
            type = FloorType::Door;
            break;
        case '.':
            type = FloorType::Tile;
            break;
        case '/':
            type = FloorType::Staircase;
            break;
        case '@':
            type = FloorType::Player;
            break;
        case 'V':
        case 'W':
        case 'T':
        case 'N':
        case 'M':
        case 'D':
        case 'X':
            type = FloorType::Enemy;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            type = FloorType::Item;
            break;
    }
}

void Cell::setEntity(Entity* e) {
    this->e = e;
}

void Cell::setNeighbours(std::vector<Cell*> neighbours) {
    this->neighbours = neighbours;
}

void Cell::setIsStairCase(bool isStairCase) {
    this->isStairCase = isStairCase;
    if (isStairCase) {
        type = FloorType::Staircase;
    } else {
        type = FloorType::Tile;
    }
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

std::vector<Cell*> Cell::getNeighbours() {
    return this->neighbours;
}

Entity* Cell::getEntity() {
    return this->e;
}
