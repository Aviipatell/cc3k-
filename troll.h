#ifndef _TROLL_H_
#define _TROLL_H_

#include "enemy.h"

class Troll : public Enemy {
    public:
        Troll(int maxHealth=120, int attack=25, int defence=15, std::string race="Troll");

        // Getters
        char getSymbol() override;

        // Helpers
        std::string attack(Player* p) override;
        std::string specialAbility(Player* p = nullptr) override;
};

#endif
