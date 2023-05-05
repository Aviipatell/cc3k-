#include "waStatus.h"

WAStatus::WAStatus(Player* next, StatusDuration duration) : StatusEffect{next, duration} {
    int attack = next->getAttack();
    attack-= 5;
    if (attack <= 0) {
        attack = 0;
    }
    next->setAttack(attack);
};

// int WAStatus::getAttack() {
//     int attack = next->getAttack();
//     attack-= 5;
//     return attack;
// }
