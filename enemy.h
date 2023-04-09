#ifndef _ENEMY_H_
#define _ENEMY_H

#include "character.h"

enum EnemyType {
    NoEnemy=0,
    Vampire,
    Werewolf,
    Troll,
    Goblin,
    Merchant,
    Dragon,
    Phoenix
};

// modify parsing bounds for additional DLC items
// enum ItemType {
//     NoItem=0,
//     Compass,
//     BarrierSuit,
//     RHPotion,
//     BAPotion,
//     BDPotion,
//     PHPotion,
//     WAPotion,
//     BDPotion,
//     Gold,
//     SmallHoard,
//     MerchantHoard,
//     DragonHoard
// };

enum AbilityType {
    NoAbility=0,
    PassiveAbility,
    ActiveAbility
};

class Player;

class Enemy : public Character {

    bool isHostile;
    bool isGuardingItem;
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
        void setIsGuardingItem(bool isGuardingItem);
        void setHasItem(bool hasItem);
        void setItemType(char itemSymbol);
        void setHasAbility(bool hasAbility);
        void setAbilityType(AbilityType abilityType);

        // Getters
        bool getIsHostile() const;
        bool getIsGuardingItem() const;
        bool getHasCompass() const;
        bool getHasItem() const;
        char getItemSymbol() const;
        bool getHasAbility() const;
        AbilityType getAbilityType() const;

        // Helpers
        virtual void attack(Player* p) = 0;
        virtual void specialAbility(Player* p = nullptr) = 0;
};
#endif
