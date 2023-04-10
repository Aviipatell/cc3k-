#include <sstream>

#include "orc.h"

Orc::Orc(int maxHealth, int attack, int defence, std::string race) : Player{maxHealth, attack, defence, race} {};

std::string Orc::incrementPlayerGold(double gold) {
    gold/= 2;
    std::ostringstream o;
    o << "PC picked up " << gold << " gold.";

    // perk: gold double value
    this->gold+= gold;

    return o.str();
}
