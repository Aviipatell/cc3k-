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
        int getMaxHealth();
        int getHealth();
        virtual int getAttack();
        virtual int getDefence();
        std::string getRace() const;
        // Helpers
        bool isDead();
};

#endif
