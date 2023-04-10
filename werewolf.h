#ifndef _WEREWOLF_H_
#define _WEREWOLF_H_

#include "enemy.h"

class Werewolf : public Enemy {
    public:
        Werewolf(int maxHealth=120, int attack=30, int defence=5, std::string race="Werewolf");

        // Getters
        char getSymbol() override;

        // Helpers (for special functionality)
        // std::string attack(Player* p) override;
        // std::string specialAbility(Player* p = nullptr) override;
};

#endif
