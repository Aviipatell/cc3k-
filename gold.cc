#include "gold.h"
#include <sstream>
#include <iostream>
#include "player.h"

Gold::Gold(bool needsProtection, char type) : Item{needsProtection} {
    setGoldType(type);
}

void Gold::setGoldAmount(int amount) {
    this->amount = amount;
}

int Gold::getGoldAmount() const {
    return this->amount;
}

void Gold::setGoldType(char type) {
    GoldType goldType;
    if (type == '6') {
        goldType = GoldType::NormalHoard;
        amount = 1;
    } else if (type == '7') {
        goldType = GoldType::SmallHoard;
        amount = 2;
    } else if (type == '8') {
        goldType = GoldType::MerchantHoard;
        amount = 4;
    } else if (type == '9') {
        goldType = GoldType::DragonHoard;
        amount = 6;
    }
    this->goldType = goldType;
}

GoldType Gold::getGoldType() const {
    return this->goldType;
}

std::string Gold::useItem(Player* p) {
    std::ostringstream o;
    std::cout << "useItem reached" << std::endl;
    o << p->incrementPlayerGold(amount);
    return o.str();
}

char Gold::getSymbol() {
    return 'G';
}
