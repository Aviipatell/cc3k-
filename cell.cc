#include "cell.h"

// Cell constructor

Cell::Cell(int row, int column, char symbol) : pos{Position{.row = row, .column = column}}, symbol{symbol} {
    this->type = determineCellType(symbol);
}

FloorType Cell::determineCellType(char symbol) {
     if (symbol == '@') {
        return FloorType::player;
    } else if (symbol == '/') {
        return FloorType::staircase;
    } else if (symbol == ' ') {
        return FloorType::blank;
    } else if (symbol == '|' || symbol == '-') {
        return FloorType::wall;
    } else if (symbol == '+') {
        return FloorType::door;
    } else if (symbol == '#') {
        return FloorType::passage;
    } else if (symbol == 'V' || symbol == 'W' || symbol == 'N' || symbol == 'M' || symbol == 'D' || symbol == 'X' || symbol == 'T') {
        return FloorType::enemy;
    } else if (symbol == '0' || symbol == '1' || symbol == '2' || symbol == '3' || symbol == '4' || symbol == '5') {
        return FloorType::item;
    } else if (symbol == '6' || symbol == '7' || symbol == '8' || symbol == '9') {
        return FloorType::item;
    }
}

// Setter functions

void Cell::setEntity(Entity* e) {
    this->e = e;
}

// should only be called once per cell, after grid generation?
void Cell::setNeighbours() {

}

void Cell::setIsStairCase(bool b) {
    this->isStairCase = true;
    if (b) {
        type = FloorType::staircase;
    } else {
        type = FloorType::tile; // TODO: confirm if I need this else condition
    }
}

void Cell::setChamber(int val) {
    this->chamber = val;
}

// Getter functions

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



// generateItem(char symbol) will take in a numeric identifier for the specific type of potion since otherwise, all potions are identified with the same 'P' symbol. Then,
