#ifndef _PHOENIX_H_
#define _PHOENIX_H_

#include "enemy.h"

class Phoenix : public Enemy {
    public:
        Phoenix(int maxHealth=50, int attack=35, int defence=20, std::string race="Phoenix");

        // Getters
        char getSymbol() override;

        // Helpers
        std::string attack(Player* p) override;
        std::string specialAbility(Player* p = nullptr) override;
};

#endif
