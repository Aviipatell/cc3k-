#include "compass.h"
#include "player.h"
#include <sstream>

Compass::Compass(bool needsProtection) : Item{needsProtection} {};

char Compass::getSymbol() {
    return 'C';
}

std::string Compass::useItem(Player* p) {
    p->setHasCompass(true);

    std::ostringstream o;
    o << "PC picked up Compass. ";
    return o.str();
}
