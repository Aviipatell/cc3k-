#ifndef __POTION_H_
#define __POTION_H_

#include "item.h"
#include <string.h>

enum PotionDuration { Temporary, Permanent };

// enum PotionType { RH, BA, BD, PH, WA, WD };

class Potion: public Item {
    PotionDuration duration;
    // PotionType type;
    string effect;
    bool isKnownPotion;
public:
    PotionDuration getDuration();
    // PotionType getType();
    string getEffect();
    bool getIsKnownPotion();
    void setIsKnownPotion(bool b);
};
