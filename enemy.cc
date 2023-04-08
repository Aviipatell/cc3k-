#include "enemy.h"

// Constructor

Enemy::Enemy(int maxHealth, int attack, int defence, std::string race) : Character{maxHealth, attack, defence, race} {};

// Setters

void Enemy::setIsHostile(bool isHostile) {
    this->isHostile = isHostile;
}

void Enemy::setHasCompass(bool hasCompass) {
    this->hasCompass = hasCompass;
}

void Enemy::setHasItem(bool hasItem) {
    this->hasItem = hasItem;
}

void Enemy::setItemType(ItemType itemType) {
    this->itemType = itemType;
}

void Enemy::setHasAbility(bool hasAbility) {
    this->hasAbility = hasAbility;
}

void Enemy::setAbilityType(AbilityType abilityType) {
    this->abilityType = abilityType;
}

// Getters

bool Enemy::getIsHostile() const {
    return isHostile;
}

bool Enemy::getHasCompass() const {
    return hasCompass;
}

bool Enemy::getHasItem() const {
    return hasItem;
}

ItemType Enemy::getItemType() const {
    return itemType;
}

bool Enemy::getHasAbility() const {
    return hasAbility;
}

AbilityType Enemy::getAbilityType() const {
    return abilityType;
}

// Helpers
