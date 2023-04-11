#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "player.h"

class Human : public Player {
    public:
        Human(int maxHealth=140, int attack=20, int defence=20, std::string race="Human");
        ~Human() {};
        double getScore() const override;
};

#endif
