#include "rhStatus.h"

RHStatus::RHStatus(Player* next, StatusDuration duration) : StatusEffect{next, duration} {
    int health = next->getHealth();
    health += 10;
    if (health > next->getMaxHealth()) {
        health = next->getMaxHealth();
    }
    next->setHealth(health);
};
