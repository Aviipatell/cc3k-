#include "barrierSuit.h"
#include "player.h";

BarrierSuit::BarrierSuit(bool needsProtection) : Item{needsProtection} {};

char BarrierSuit::getSymbol() {
    return 'B';
}

std::string BarrierSuit::useItem(Player* p) {
    p->setHasBarrierSuit(true);
}
