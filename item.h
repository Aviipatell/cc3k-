#ifndef _ITEM_H_
#define _ITEM_H_

#include "entity.h"
class Player;
class Enemy;

class Item: public Entity {

    char protectorType;
    bool needsProtection;
    bool isProtected;

public:
    Item(bool needsProtection);

    void setProtectorType(char protectorType);
    void setNeedsProtection(bool needsProtection);
    void setIsProtected(bool isProtected);

    char getProtectorType() const;
    bool getNeedsProtection() const;
    bool getIsProtected() const;

    void checkProtectors(Enemy* enemyToDelete);
    virtual std::string useItem(Player* p) = 0;
};

#endif
