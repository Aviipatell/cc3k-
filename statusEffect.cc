#include "statusEffect.h"

// Constructor
StatusEffect::StatusEffect(Player* next, StatusDuration duration) : next{next}, duration{duration} {};

// Destructor
StatusEffect::~StatusEffect() {
    // TODO: set up cool logic here to selectively destroy
    delete next;
}

int StatusEffect::getHealth() {
    int health = next->getHealth();
    return health;
}

int StatusEffect::getAttack() {
    int attack = next->getAttack();
    return attack;
}

int StatusEffect::getDefence() {
    int defence = next->getDefence();
    return defence;
}

// TODO: might not reference the specific status's getHealth() function?
bool StatusEffect::isDead() {
    int health = next->getHealth();
    return health == 0;
}
