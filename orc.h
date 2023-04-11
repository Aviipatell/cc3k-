#ifndef _ORC_H_
#define _ORC_H_

#include "player.h"

class Orc : public Player {
    public:
        Orc(int maxHealth=180, int attack=30, int defence=25, std::string race="Orc");
        ~Orc() {};
        std::string incrementPlayerGold(double gold) override;
};

#endif
