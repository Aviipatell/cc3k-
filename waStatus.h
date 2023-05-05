#ifndef _WA_STATUS_H_
#define _WA_STATUS_H_

#include "statusEffect.h"

class WAStatus : public StatusEffect {
    public:
        WAStatus(Player* next, StatusDuration duration=StatusDuration::Temporary);
        // int getAttack() override;
};

#endif
