#ifndef __GOLD_H_
#define __GOLD_H_

#include "item.h"

// enum GoldType{ Normal, SmallHoard, MerchantHoard };

class Gold: public Item {
    GoldType type;
public:
    void useItem() override;
};
