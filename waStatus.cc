#include "waStatus.h"

WAStatus::WAStatus(Player* next, StatusDuration duration) : StatusEffect{next, duration} {};

int WAStatus::getAttack() {
    int attack = next->getAttack();
    attack-= 5;
    return attack;
}
