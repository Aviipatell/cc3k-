#include "rhStatus.h"

RHStatus::RHStatus(Player* next, StatusDuration duration) : StatusEffect{next, duration} {
    int health = getHealth();
    health+= 10;
    if (health > getMaxHealth()) {
        health = getMaxHealth();
    }
    setHealth(health);
};
