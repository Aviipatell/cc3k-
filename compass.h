#ifndef _COMPASS_H_
#define _COMPASS_H_

#include "item.h"
#include <string>

class Player;

class Compass : public Item {
    public:
        Compass(bool needsProtection);
        ~Compass() {};

        char getSymbol() override;
        std::string useItem(Player* p) override;
};

#endif
