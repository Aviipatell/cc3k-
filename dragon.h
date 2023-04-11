#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "enemy.h"

class Dragon : public Enemy {
    public:
        Dragon(int maxHealth=150, int attack=20, int defence=20, std::string race="Dragon");

        // Getters
        char getSymbol() override;

        // Helpers
        std::string specialAbility(Player* p = nullptr) override;
};

#endif
