#ifndef _BA_STATUS_H_
#define _BA_STATUS_H_

#include "statusEffect.h"

class BAStatus : public StatusEffect {
    public:
        BAStatus(Player* next, StatusDuration duration=StatusDuration::Temporary);
        // int getAttack() override;
};

#endif
