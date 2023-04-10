#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"

class Enemy;

class Player: public Character {

    protected:
        double gold;
        bool hasBarrierSuit;
    // Add Player Inventory here

    public:
        // Constructors // TODO: figure out another way if possible?
        Player(int maxHealth=0, int attack=0, int defence=0, std::string race="");
        // Setters
        void setPlayerGold(double gold);
        void setHasBarrierSuit(bool hasBarrierSuit);
        // Getters
        int getPlayerGold() const;
        bool getHasBarrierSuit() const;
        char getSymbol() override;

        // Helpers
        virtual std::string incrementPlayerGold(double gold);
        virtual std::string attack(Enemy* e);
        virtual double getScore() const;

        // Inventory/Weapon specific methods go here
};

#endif
