#ifndef _STATUS_EFFECT_H_
#define _STATUS_EFFECT_H_

#include "player.h"

enum StatusDuration {
    Temporary=0,
    Permenant
};

class StatusEffect : public Player {
    protected:
        Player* next = nullptr;
        StatusDuration duration;
    public:
        // Constructor
        StatusEffect(Player* next, StatusDuration duration);
        // Destructor
        ~StatusEffect();
        // Helpers
        int getHealth() override;
        int getAttack() override;
        int getDefence() override;
        bool isDead() override;
};

#endif
