#ifndef _DWARF_H_
#define _DWARF_H_

#include "player.h"

class Dwarf : public Player {
    public:
        Dwarf(int maxHealth=100, int attack=20, int defence=30, std::string race="Dwarf");
        std::string incrementPlayerGold(double gold) override;
};

#endif
