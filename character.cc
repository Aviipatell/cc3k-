#include "character.h"

// Constructor
Character::Character(int maxHealthPoints, int attackPoints, int defencePoints, std::string race) : maxHealthPoints{maxHealthPoints}, healthPoints{maxHealthPoints}, attackPoints{attackPoints}, defencePoints{defencePoints}, race{race} {};

// Setters

void Character::setMaxHealthPoints(int maxHealthPoints) {
    if (maxHealthPoints <= 0) {
        this->maxHealthPoints = 1;
    } else {
        this->maxHealthPoints = maxHealthPoints;
    }
}

void Character::setHealthPoints(int healthPoints) {
    if (healthPoints < 0) {
        this->healthPoints = 0;
    } else {
        this->healthPoints = healthPoints;
    }
}

void Character::setAttackPoints(int attackPoints) {
    if (attackPoints < 0) {
        this->attackPoints = 0;
    } else {
        this->attackPoints = attackPoints;
    }
}

void Character::setDefencePoints(int defencePoints) {
    if (defencePoints < 0) {
        this->defencePoints = 0;
    } else {
        this->defencePoints = defencePoints;
    }
}

void Character::setRace(std::string race) {
    this->race = race;
}

// Getters

int Character::getMaxHealthPoints() const {
    return maxHealthPoints;
}

int Character::getHealthPoints() const {
    return healthPoints;
}

int Character::getAttackPoints() const {
    return attackPoints;
}

int Character::getDefencePoints() const {
    return defencePoints;
}

std::string Character::getRace() const {
    return race;
}

// Helpers

bool Character::isDead() const {
    return healthPoints == 0;
}
