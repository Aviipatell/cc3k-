#ifndef _GOLD_H_
#define _GOLD_H_

#include "item.h"

class Player; // TODO: remember to go back and set up forward declaration in headers to avoid circular dependencies

enum GoldType {
    Normal=0,
    SmallHoard,
    MerchantHoard,
    DragonHoard
};

class Gold : public Item {
    GoldType goldType;
    double amount = 1;
    public:
        Gold(char protectorType, bool needsProtection, bool isProtected, char goldType);

        char getSymbol() override;
        void setGoldType(char goldType);

        GoldType getGoldType() const {
            return goldType;
        }

        std::string useItem(Player* p) override;
};

#endif
