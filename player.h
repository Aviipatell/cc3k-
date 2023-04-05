#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "character.h"

class Enemy;

class Player: public Character {
    int gold;
public:
    int getPlayerGold();
    void setPlayerGold(int val);
    virtual void attack(Enemy &e) = 0;
    virtual void specialAbility() = 0;
};

class Human: public Player {
public:
    void attack(Enemy &e) override;
    void specialAbility() override;
};

class Elf: public Player {
public:
    void attack(Enemy &e) override;
    void specialAbility() override;
};

class Orc: public Player {
public:
    void attack(Enemy &e) override;
    void specialAbility() override;
};

class Dwarf: public Player {
public:
    void attack(Enemy &e) override;
    void specialAbility() override;
};

#endif
