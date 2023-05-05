#include "wdStatus.h"

WDStatus::WDStatus(Player* next, StatusDuration duration) : StatusEffect{next, duration} {
    int defence = next->getDefence();
    defence-= 5;
    next->setDefence(defence);
};

// int WDStatus::getDefence() {
//     int defence = next->getDefence();
//     defence-= 5;
//     return defence;
// }
