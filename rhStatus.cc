#include "rhStatus.h"

RHStatus::RHStatus(Player* next, StatusDuration duration) : StatusEffect{next, duration} {};

int RHStatus::getHealth() {
    // apply other effects, and then stack on this new effect
    int health = next->getHealth();
    health+= 10;
    if (health > next->getMaxHealth()) {
        health = next->getMaxHealth();
    }
    return health;
}
