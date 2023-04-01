#ifndef __BARRIER_SUIT_H_
#define __BARRIER_SUIT_H_

#include "protected_item.h"

class BarrierSuit: public ProtectedItem {
public:
    void useItem() override;
};
