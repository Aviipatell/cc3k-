#ifndef _BARRIER_SUIT_H_
#define _BARRIER_SUIT_H_

#include "item.h"
#include <string>

class Player;

class BarrierSuit : public Item {
    public:
        BarrierSuit(bool needsProtection);
        char getSymbol() override;
        std::string useItem(Player*) override;
};

#endif
