#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include "entity.h"

class Character: public Entity {
    int maxHealth;
    int health;
    int attack;
    int defence;
    std::string race;

    public:
        // Constructor
        Character(int maxHealth, int attack, int defence, std::string race);
        virtual ~Character() = 0;
        // Setters
        void setMaxHealth(int maxHealth);
        void setHealth(int health);
        void setAttack(int attack);
        void setDefence(int defence);
        void setRace(std::string race);
        // Getters
        int getMaxHealth() const;
        int getHealth() const;
        int getAttack() const;
        int getDefence() const;
        std::string getRace() const;
        // Helpers
        bool isDead() const;
};

#endif

// Character::Character(...)
// -> do we do anything with Entity superclass?

// Character::getters/settings, default behaviour

// Character::isDead()
// -> return true if attackPoints == 0
