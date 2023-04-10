#include "compass.h"
#include "player.h";

Compass::Compass(char protectorType, bool needsProtection, bool isProtected) : Item{protectorType, needsProtection, isProtected} {};

char Compass::getSymbol() {
    return 'C';
}

std::string Compass::useItem(Player* p) {
    p->setHasBarrierSuit(true);
}
