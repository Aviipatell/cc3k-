#include "bdStatus.h"

BDStatus::BDStatus(Player* next, StatusDuration duration) : StatusEffect{next, duration} {};

int BDStatus::getDefence() {
    int defence = next->getDefence();
    defence+= 5;
    return defence;
}
