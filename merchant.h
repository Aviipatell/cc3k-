#ifndef _MERCHANT_H_
#define _MERCHANT_H_

#include "enemy.h"

class Merchant : public Enemy {
    public:
        Merchant(int maxHealth=30, int attack=70, int defence=5, std::string race="Merchant");

        // Getters
        char getSymbol() override;

        // Helpers
        // std::string attack(Player* p) override;
        // std::string specialAbility(Player* p = nullptr) override;
};

#endif
