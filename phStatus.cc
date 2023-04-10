#include "phStatus.h"

PHStatus::PHStatus(Player* next, StatusDuration duration) : StatusEffect{next, duration} {};

int PHStatus::getHealth() {
    // apply other effects, and then stack on this new effect
    int health = next->getHealth();
    health-= 10;
    if (health < 0) {
        health = 0;
    }
    return health;
}
