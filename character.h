#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include "entity.h"

class Character: public Entity {
    int maxHealthPoints;
    int healthPoints;
    int attackPoints;
    int defencePoints;
    std::string race;

    public:
        // Constructor
        Character(int maxHealthPoints, int attackPoints, int defencePoints, std::string race);
        // Setters
        void setMaxHealthPoints(int maxHealthPoints);
        void setHealthPoints(int healthPoints);
        void setAttackPoints(int attackPoints);
        void setDefencePoints(int defencePoints);
        void setRace(std::string race);
        // Getters
        int getMaxHealthPoints() const;
        int getHealthPoints() const;
        int getAttackPoints() const;
        int getDefencePoints() const;
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
