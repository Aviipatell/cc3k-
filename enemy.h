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

    bool isHostile = true;
    bool isGuardian = false;
    bool hasItem = false;
    char itemSymbol;

    std::vector<Item*> guardedItems; // 1..*

    bool hasAbility = false;
    AbilityType aType = AbilityType::NoAbility;

    bool hasAlreadyMoved = false;

    public:
        // Constructor
        Enemy(int maxHealth, int attack, int defence, std::string race);

        // Setters
        void setIsHostile(bool isHostile);
        void setIsGuardian(bool isGuardian);
        void setHasItem(bool hasItem);
        void setItemSymbol(char itemSymbol);
        void setGuardedItems(std::vector<Item*> guardedItems);
        void setHasAbility(bool hasAbility);
        void setAbilityType(AbilityType aType);
        void setHasAlreadyMoved(bool hasAlreadyMoved);

        // Getters
        bool getIsHostile() const;
        bool getIsGuardian() const;
        bool getHasItem() const;
        char getItemSymbol() const;
        bool getHasAbility() const;
        bool getHasAlreadyMoved() const;
        AbilityType getAbilityType() const;
        std::vector<Item*> getGuardedItems() const;

        // Helpers
        virtual std::string attack(Player* p);
        virtual std::string specialAbility(Player* p = nullptr) = 0;
};
#endif
