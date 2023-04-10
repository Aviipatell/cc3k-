#include "cmath"

#include "human.h"

Human::Human(int maxHealth, int attack, int defence, std::string race) : Player{maxHealth, attack, defence, race} {};

double Human::getScore() const {
    return std::ceil(this->gold * 1.5);
}
