#include "statusEffect.h"

// Constructor
StatusEffect::StatusEffect(Player* next, StatusDuration duration) : next{next}, duration{duration} {};

// Destructor
StatusEffect::~StatusEffect() {
    delete next;
}

// int StatusEffect::getAttack() {
//     int attack = next->getAttack();
//     return attack;
// }

// int StatusEffect::getDefence() {
//     int defence = next->getDefence();
//     return defence;
// }

StatusDuration StatusEffect::getStatusDuration() const {
    return this->duration;
}

Player* StatusEffect::getNext() const {
    return this->next;
}
