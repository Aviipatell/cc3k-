#include "barrierSuit.h"
#include "player.h";

BarrierSuit::BarrierSuit(char protectorType, bool needsProtection, bool isProtected) : Item{protectorType, needsProtection, isProtected} {};

char BarrierSuit::getSymbol() {
    return 'B';
}

std::string useItem(Player* p) {
    p->setHasBarrierSuit(true);
}
