#ifndef _POTION_H
#define _POTION_H

#include "item.h"
#include <string>

class Player;

enum PotionType {
    RHPotion=0,
    BAPotion,
    BDPotion,
    PHPotion,
    WAPotion,
    WDPotion
};

class Potion : public Item {

    PotionType potionType;

    public:
        Potion(char potionType, char protectorType='0', bool needsProtection=false, bool isProtected=false);

        char getSymbol() override;
        void setPotionType(char potionType);
        PotionType getPotionType() const;
        std::string getEffect() const;
        std::string useItem(Player* p) override;
};

#endif
