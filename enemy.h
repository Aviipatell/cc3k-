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
    Phenoix
};

// modify parsing bounds for additional DLC items
enum ItemType {
    NoItem=0,
    Compass,
    BarrierSuit,
    RHPotion,
    BAPotion,
    BDPotion,
    PHPotion,
    WAPotion,
    BDPotion,
    Gold,
    SmallHoard,
    MerchantHoard,
    DragonHoard
};

enum AbilityType {
    NoAbility=0,
    PassiveAbility,
    ActiveAbility
};

class Player;

class Enemy : public Character {

    bool isHostile;
    bool hasCompass; // don't need, refactor out later
    bool hasItem;
    ItemType itemType;
    bool hasAbility;
    AbilityType abilityType;

    public:
        // Constructor
        Enemy(int maxHealth, int attack, int defence, std::string race);
        // shouldn't need to create pure virutal dtor, bc superclass dtor carries over

        // Setters
        void setIsHostile(bool isHostile);
        void setHasCompass(bool hasCompass);
        void setHasItem(bool hasItem);
        void setItemType(ItemType itemType);
        void setHasAbility(bool hasAbility);
        void setAbilityType(AbilityType abilityType);

        // Getters
        bool getIsHostile() const;
        bool getHasCompass() const;
        bool getHasItem() const;
        ItemType getItemType() const;
        bool getHasAbility() const;
        AbilityType getAbilityType() const;

        // Helpers
        virtual void attack(Player* p) = 0;
        virtual void specialAbility(Player* p = nullptr) = 0;
};
#endif
