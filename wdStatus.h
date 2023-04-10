#ifndef _WD_STATUS_H_
#define _WD_STATUS_H_

#include "statusEffect.h"

class WDStatus : public StatusEffect {
    public:
        WDStatus(Player* next, StatusDuration duration=StatusDuration::Temporary);
        int getDefence() override;
};

#endif
