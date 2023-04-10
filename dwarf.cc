#include <sstream>

#include "dwarf.h"

Dwarf::Dwarf(int maxHealth, int attack, int defence, std::string race) : Player{maxHealth, attack, defence, race} {};

std::string Dwarf::incrementPlayerGold(double gold) {
    gold*= 2;
    std::ostringstream o;
    o << "PC picked up " << gold << " gold.";

    // perk: gold double value
    this->gold+= gold;

    return o.str();
}
