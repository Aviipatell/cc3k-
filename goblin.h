#ifndef _GOBLIN_H_
#define _GOBLIN_H_

#include "enemy.h"
#include <vector>

class Goblin : public Enemy {
    public:
        Goblin(int maxHealth=70, int attack=5, int defence=10, std::string race="Goblin");

        // Getters
        char getSymbol() override;

        // Helpers
        std::string attack(Player* p) override;
        std::string specialAbility(Player* p = nullptr) override;
};

#endif
