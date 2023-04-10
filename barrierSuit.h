#ifndef _BARRIER_SUIT_H_
#define _BARRIER_SUIT_H_

#include "item.h"
#include <string>

class Player;

class BarrierSuit : public Item {
    public:
        BarrierSuit(char protectorType, bool needsProtection, bool isProtected);
        char getSymbol() override;
        std::string useItem(Player*) override;
};

#endif
