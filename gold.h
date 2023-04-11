#ifndef _GOLD_H_
#define _GOLD_H_

#include "item.h"

class Player;

enum GoldType {
    Normal=0,
    SmallHoard,
    MerchantHoard,
    DragonHoard
};

class Gold : public Item {
    GoldType goldType;
    double amount;
    public:
        Gold(bool needsProtection, char type);

        void setGoldType(char goldType);
        void setGoldAmount(int amount);
        int getGoldAmount() const;
        GoldType getGoldType() const;


        char getSymbol() override;
        std::string useItem(Player* p) override;
};

#endif
