#include "baStatus.h"

BAStatus::BAStatus(Player* next, StatusDuration duration) : StatusEffect{next, duration} {};

int BAStatus::getAttack() {
    int attack = next->getAttack();
    attack+= 5;
    return attack;
}