#ifndef __CHARACTER_H_
#define __CHARACTER_H_

#include <string.h>
#include "entity.h"

class Character: public Entity {
    int healthPoints;
    int attackPoints;
    int defencePoints;
    std::string race;
public:
    int getHealthPoints();
    int getAttackPoints();
    int getDefencePoints();
    std::string getRace();
    void setHealthPoints(int val);
    void setAttackPoints(int val);
    void setDefencePoints(int val);
    void setRace(std::string race);

    bool isAlive();
};

#endif
