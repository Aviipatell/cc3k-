#ifndef _PH_STATUS_H_
#define _PH_STATUS_H_

#include "statusEffect.h"

class PHStatus : public StatusEffect {
    public:
        PHStatus(Player* next, StatusDuration duration=StatusDuration::Permenant);
        int getHealth() override;
};

#endif
