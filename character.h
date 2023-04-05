#ifndef __CHARACTER_H_
#define __CHARACTER_H_

#include <string>
#include "entity.h"

class Character: public Entity {
    int healthPoints;
    int attackPoints;
    int defencePoints;
    std::string race;

    public:
        Character(int healthPoints, int attackPoints, int defencePoints, std::string race);
        int getHealthPoints() const;
        int getAttackPoints() const;
        int getDefencePoints() const;
        std::string getRace() const;

        void setHealthPoints(int val);
        void setAttackPoints(int val);
        void setDefencePoints(int val);
        void setRace(std::string race);

        bool isDead() const;
};

#endif

// Character::Character(...)
// -> do we do anything with Entity superclass?

// Character::getters/settings, default behaviour

// Character::isDead()
// -> return true if attackPoints == 0
