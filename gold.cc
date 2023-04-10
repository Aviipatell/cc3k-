#include "gold.h"
#include <sstream>

#include "player.h"

Gold::Gold(char protectorType, bool needsProtection, bool isProtected, char goldType) : Item{protectorType, needsProtection, isProtected} {
    setGoldType(goldType);
};

void Gold::setGoldType(char goldType) {
    GoldType type;
    if (goldType == '6') {
        type = GoldType::Normal;
        amount = 1;
    } else if (goldType == '7') {
        type = GoldType::SmallHoard;
        amount = 2;
    } else if (goldType == '8') {
        type = GoldType::MerchantHoard;
        amount = 4;
    } else if (goldType == '9') {
        type = GoldType::DragonHoard;
        amount = 6;
    }
    this->goldType = type;
}

GoldType Gold::getGoldType() const {
    return this->goldType;
}

std::string Gold::useItem(Player* p) {
    std::ostringstream o;

    o << p->incrementPlayerGold(amount);
    return o.str();
}
