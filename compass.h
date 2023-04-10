#ifndef _COMPASS_H_
#define _COMPASS_H_

#include "item.h"
#include <string>

class Player;

class Compass : public Item {
    public:
        Compass(char protectorType, bool needsProtection, bool isProtected);
        char getSymbol() override;
        std::string useItem(Player*) override;
};

#endif
