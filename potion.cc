#include "potion.h"

#include "rhStatus.h"
#include "baStatus.h"
#include "bdStatus.h"
#include "phStatus.h"
#include "waStatus.h"
#include "wdStatus.h"

Potion::Potion(bool needsProtection, char type) : Item{needsProtection} {
    setPotionType(type);
};

void Potion::setPotionType(char type) {
    PotionType potionType;
    if (type == '0') {
        potionType = PotionType::RHPotion;
    } else if (type == '1') {
        potionType = PotionType::BAPotion;
    } else if (type == '2') {
        potionType = PotionType::BDPotion;
    } else if (type == '3') {
        potionType = PotionType::PHPotion;
    } else if (type == '4') {
        potionType = PotionType::WAPotion;
    } else {
        potionType = PotionType::WDPotion;
    }
    this->potionType = potionType;
}

PotionType Potion::getPotionType() const {
    return this->potionType;
}

std::string Potion::getEffect() const {
    std::string effect;
    if (potionType == PotionType::RHPotion) {
        effect = "Restores up to 10 HP.";
    } else if (potionType == PotionType::BAPotion) {
        effect = "Increases ATK by 5.";
    } else if (potionType == PotionType::BDPotion) {
        effect = "Increases DEF by 5.";
    } else if (potionType == PotionType::PHPotion) {
        effect = "Lose up to 10 HP.";
    } else if (potionType == PotionType::WAPotion) {
        effect = "Decrease ATK by 5.";
    } else {
        effect = "Decrease DEF by 5.";
    }
    return effect;
}

std::string Potion::useItem(Player* p) {
    std::string msg;
    if (potionType == PotionType::RHPotion) {
        p = new RHStatus{p};
        msg = "PC uses RH.";
    } else if (potionType == PotionType::BAPotion) {
        p = new BAStatus{p};
        msg = "PC uses BA.";
    } else if (potionType == PotionType::BDPotion) {
        p = new BDStatus{p};
        msg = "PC uses BD.";
    } else if (potionType == PotionType::PHPotion) {
        p = new PHStatus{p};
        msg = "PC uses PH.";
    } else if (potionType == PotionType::WAPotion) {
        p = new WAStatus{p};
        msg = "PC uses WA.";
    } else {
        p = new WDStatus{p};
    }
    return msg;
}

char Potion::getSymbol() {
    return 'P';
}
