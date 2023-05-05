#include "phStatus.h"

PHStatus::PHStatus(Player* next, StatusDuration duration) : StatusEffect{next, duration} {
    int health = next->getHealth();
    health-= 10;
    if (health <= 0) {
        health = 0;
    }
    next->setHealth(health);
};
