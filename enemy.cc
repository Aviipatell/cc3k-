#include <sstream>
#include <vector>
#include <cmath>
#include "enemy.h"
#include "player.h"
#include "item.h"

// Constructor

Enemy::Enemy(int maxHealth, int attack, int defence, std::string race) : Character{maxHealth, attack, defence, race} {};

// Setters

void Enemy::setIsHostile(bool isHostile) {
    this->isHostile = isHostile;
}

void Enemy::setIsGuardian(bool isGuardian) {
    this->isGaurdian = isGuardian;
}

void Enemy::setHasItem(bool hasItem) {
    this->hasItem = hasItem;
}

void Enemy::setItemSymbol(char itemSymbol) {
    this->itemSymbol = itemSymbol;
}

void Enemy::setHasAbility(bool hasAbility) {
    this->hasAbility = hasAbility;
}

void Enemy::setAbilityType(AbilityType abilityType) {
    this->abilityType = abilityType;
}

void Enemy::setGuardedItems(std::vector<Item*> guardedItems) {
    this->guardedItems = guardedItems;
}

// Getters

bool Enemy::getIsHostile() const {
    return isHostile;
}

bool Enemy::getHasItem() const {
    return hasItem;
}

char Enemy::getItemSymbol() const {
    return itemSymbol;
}

bool Enemy::getHasAbility() const {
    return hasAbility;
}

AbilityType Enemy::getAbilityType() const {
    return abilityType;
}

std::vector<Item*> Enemy::getGuardedItems() const {
    return guardedItems;
}

// Helpers
std::string Enemy::attack(Player* p) {
    std::ostringstream o;

    int damage = std::ceil((100.0/(100+p->getDefence()))) * this->getAttack();
    if (p->getHasBarrierSuit()) damage = std::ceil(damage/2);
    p->setHealth(damage);

    o << getSymbol() << " deals " << damage << " to " << p->getSymbol() << ".";
    return o.str();
}
