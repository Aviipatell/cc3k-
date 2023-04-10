#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_

#include "enemy.h"

class Vampire : public Enemy {
    public:
        Vampire(int maxHealth=50, int attack=25, int defence=25, std::string race="Vampire");

        // Getters
        char getSymbol() override;

        // Helpers
        std::string attack(Player* p) override;
        std::string specialAbility(Player* p = nullptr) override;
};

#endif
