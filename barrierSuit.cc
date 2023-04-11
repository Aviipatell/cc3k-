#include "barrierSuit.h"

#include "player.h"
#include <sstream>

BarrierSuit::BarrierSuit(bool needsProtection) : Item{needsProtection} {};

char BarrierSuit::getSymbol() {
    return 'B';
}

std::string BarrierSuit::useItem(Player* p) {
    p->setHasBarrierSuit(true);

    std::ostringstream o;
    o << "PC equiped Barrier Suit. ";
    return o.str();
}
