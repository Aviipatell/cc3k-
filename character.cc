#include "character.h"

// Constructor
Character::Character(int maxHealth, int attack, int defence, std::string race) : maxHealth{maxHealth}, health{maxHealth}, attack{attack}, defence{defence}, race{race} {};

// Setters

void Character::setMaxHealth(int maxHealth) {
    if (maxHealth <= 0) {
        this->maxHealth = 1;
    } else {
        this->maxHealth = maxHealth;
    }
}

void Character::setHealth(int health) {
    if (health < 0) {
        this->health = 0;
    } else {
        this->health = health;
    }
}

void Character::setAttack(int attack) {
    if (attack < 0) {
        this->attack = 0;
    } else {
        this->attack = attack;
    }
}

void Character::setDefence(int defence) {
    if (defence < 0) {
        this->defence = 0;
    } else {
        this->defence = defence;
    }
}

void Character::setRace(std::string race) {
    this->race = race;
}

// Getters

int Character::getMaxHealth() {
    return maxHealth;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefence() {
    return defence;
}

std::string Character::getRace() const {
    return race;
}

// Helpers

bool Character::isDead() {
    return health == 0;
}
