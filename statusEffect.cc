#include "statusEffect.h"

// Constructor
StatusEffect::StatusEffect(Player* next, StatusDuration duration) : next{next}, duration{duration} {};

// Destructor
StatusEffect::~StatusEffect() {
    // TODO: set up cool logic here to selectively destroy
    delete next;
}

int StatusEffect::getAttack() {
    int attack = next->getAttack();
    return attack;
}

int StatusEffect::getDefence() {
    int defence = next->getDefence();
    return defence;
}
