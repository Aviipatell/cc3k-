#ifndef _ENEMY_H_
#define _ENEMY_H

#include "character.h"

enum AbilityType {
    NoAbility=0,
    PassiveAbility,
    ActiveAbility
};

class Player;
class Item;

class Enemy : public Character {

    bool isHostile;
    bool isGaurdian;
    std::vector<Item*> guardedItems; // 1..*
    bool hasItem;
    char itemSymbol;
    bool hasAbility;
    AbilityType abilityType;

    public:
        // Constructor
        Enemy(int maxHealth, int attack, int defence, std::string race);
        // shouldn't need to create pure virutal dtor, bc superclass dtor carries over

        // Setters
        void setIsHostile(bool isHostile);
        void setIsGuardian(bool isGuardian);
        void setHasItem(bool hasItem);
        void setItemSymbol(char itemSymbol);
        void setHasAbility(bool hasAbility);
        void setAbilityType(AbilityType abilityType);
        void setGuardedItems(std::vector<Item*> guardedItems);

        // Getters
        bool getIsHostile() const;
        bool getIsGuardian() const;
        bool getHasItem() const;
        char getItemSymbol() const;
        bool getHasAbility() const;
        AbilityType getAbilityType() const;
        std::vector<Item*> getGuardedItems() const;

        // Helpers
        virtual std::string attack(Player* p);
        virtual std::string specialAbility(Player* p = nullptr) = 0;
};
#endif
