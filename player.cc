#include <sstream>
#include <cmath>

#include "player.h"
#include "enemy.h"

// Constructor
Player::Player(int maxHealth, int attack, int defence, std::string race) : Character{maxHealth, attack, defence, race}, gold{0}, hasBarrierSuit{false} {};

// Setters
void Player::setPlayerGold(double gold) {
    this->gold = gold;
}

// Getters

int Player::getPlayerGold() const {
    return this->gold;
}

// Helpers
std::string Player::incrementPlayerGold(double gold) {
    std::ostringstream o;
    o << "PC picked up " << gold << " gold.";

    // default: just add raw value of gold
    this->gold+= gold;

    return o.str();
}

std::string Player::attack(Enemy* e) {
    std::ostringstream o;

    int damage = std::ceil((100.0/(100+e->getDefence()))) * this->getAttack();
    e->setHealth(e->getHealth() - damage);

    o << "PC deals " << damage << " to " << e->getSymbol() << " (" << e->getHealth() << " HP).";
    return o.str();
}

double Player::getScore() const {
    // default just based on Player's gold
    return this->gold;
}
