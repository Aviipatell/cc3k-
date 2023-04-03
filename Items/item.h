#ifndef __ITEM_H_
#define __ITEM_H_

class Entity;

class Item: public Entity {
public:
    virtual void useItem() = 0;

    bool isPotion();
    bool isGold();
    bool isProtected();
};

#endif
