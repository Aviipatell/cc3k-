#ifndef _ITEM_H_
#define _ITEM_H_

class Entity;

class Item: public Entity {

    char protectorType;
    bool needsProtection;
    bool isProtected;

public:
    Item(char protectorType, bool needsProtection, bool isProtected);

    void setProtectorType(char protectorType);
    void setNeedsProtection(bool needsProtection);
    void setIsProtected(bool isProtected);

    char getProtectorType() const;
    bool getNeedsProtection() const;
    bool getIsProtected() const;

    void checkProtectors(); // scan neighbours of item to see if any enemies that are isGaurding are alive.
    virtual std::string useItem(Player* p) = 0;
};

#endif
