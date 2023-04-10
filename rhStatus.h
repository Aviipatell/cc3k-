#ifndef _RH_STATUS_H_
#define _RH_STATUS_H_

#include "statusEffect.h"

class RHStatus : public StatusEffect {
    public:
        RHStatus(Player* next, StatusDuration duration=StatusDuration::Permenant);
        int getHealth() override;
};

#endif
