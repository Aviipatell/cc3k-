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
    this->isGuardian = isGuardian;
}

void Enemy::setHasItem(bool hasItem) {
    this->hasItem = hasItem;
}

void Enemy::setItemSymbol(char itemSymbol) {
    this->itemSymbol = itemSymbol;
}

void Enemy::setHasAbility(bool hasAbility) {
    // this->hasAbility = hasAbility;
}

void Enemy::setAbilityType(AbilityType aType) {
    this->aType = aType;
}

void Enemy::setGuardedItems(std::vector<Item*> guardedItems) {
    this->guardedItems = guardedItems;
}

void Enemy::setHasAlreadyMoved(bool hasAlreadyMoved) {
    this->hasAlreadyMoved = hasAlreadyMoved;
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
    return aType;
}

std::vector<Item*> Enemy::getGuardedItems() const {
    return guardedItems;
}

bool Enemy::getHasAlreadyMoved() const {
    return hasAlreadyMoved;
}

bool Enemy::getIsGuardian() const {
    return isGuardian;
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
