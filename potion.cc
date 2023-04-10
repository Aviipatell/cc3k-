#include "potion.h"
#include "rhStatus.h"
#include "baStatus.h"
#include "bdStatus.h"
#include "phStatus.h"
#include "waStatus.h"
#include "wdStatus.h"

Potion::Potion(char protectorType, bool needsProtection, bool isProtected, char potionType) : Item{protectorType, needsProtection, isProtected} {
    setPotionType(potionType);
};

void Potion::setPotionType(char potionType) {
    PotionType type;
    if (potionType == '0') {
        type = PotionType::RHPotion;
    } else if (potionType == '1') {
        type = PotionType::BAPotion;
    } else if (potionType == '2') {
        type = PotionType::BDPotion;
    } else if (potionType == '3') {
        type = PotionType::PHPotion;
    } else if (potionType == '4') {
        type = PotionType::WAPotion;
    } else {
        type = PotionType::WDPotion;
    }
    this->potionType = type;
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
        msg = "PC uses BA.";
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
