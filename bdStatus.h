#ifndef _BD_STATUS_H_
#define _BD_STATUS_H_

#include "statusEffect.h"

class BDStatus : public StatusEffect {
    public:
        BDStatus(Player* next, StatusDuration duration=StatusDuration::Temporary);
        int getDefence() override;
};

#endif
