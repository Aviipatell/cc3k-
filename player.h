#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"

class Enemy;

class Player: public Character {

    protected:
        double gold;
        bool hasBarrierSuit;
        bool hasCompass;
    // Add Player Inventory here

    public:
        // Constructors
        // Player(); // to enable StatusEffect Decorator
        Player(int maxHealth=0, int attack=0, int defence=0, std::string race="");
        // Setters
        void setPlayerGold(double gold);
        void setHasBarrierSuit(bool hasBarrierSuit);
        void setHasCompass(bool hasCompass);
        // Getters
        int getPlayerGold() const;
        bool getHasBarrierSuit() const;
        bool getHasCompass() const;
        char getSymbol() override;

        // Helpers
        virtual std::string incrementPlayerGold(double gold);
        virtual std::string attack(Enemy* e);
        virtual double getScore() const;

        // Inventory/Weapon specific methods go here
};

#endif
