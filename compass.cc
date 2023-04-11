#include "compass.h"
#include "player.h";

Compass::Compass(bool needsProtection) : Item{needsProtection} {};

char Compass::getSymbol() {
    return 'C';
}

std::string Compass::useItem(Player* p) {
    p->setHasCompass(true);
}
