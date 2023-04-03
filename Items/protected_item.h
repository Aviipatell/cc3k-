#ifndef __PROTECTED_ITEM_H_
#define __PROTECTED_ITEM_H_

#include "item.h"

class Dragon;

class ProtectedItem: public Item {
    Dragon *dragon;
public:
    void setDragon(Dragon *d);
    void destroyDragon();
};
