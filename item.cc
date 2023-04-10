#include "item.h"
#include "entity.h"
#include "cell.h" // might cause issue?
#include "enemy.h"

Item::Item(char protectorType, bool needsProtection, bool isProtected) : protectorType{protectorType}, needsProtection{needsProtection}, isProtected{isProtected} {};

void Item::setProtectorType(char protectorType) {
    this->protectorType = protectorType;
}

void Item::setNeedsProtection(bool needsProtection) {
    this->needsProtection = needsProtection;
}

void Item::setIsProtected(bool isProtected) {
    this->isProtected = isProtected;
}

char Item::getProtectorType() const {
    return protectorType;
}

bool Item::getNeedsProtection() const {
    return needsProtection;
}

bool Item::getIsProtected() const {
    return getIsProtected;
}

void Item::checkProtectors() {
    if (!needsProtection) return;
    Cell* c = getCell();
    std::vector<Cell*> neighbours = c->getNeighbours();
    bool hasProtectors = false;
    for (Cell* c : neighbours) {
        Entity* e = c->getEntity();
        if (e == nullptr) continue;
        Enemy* enemy = dynamic_cast<Enemy*>(e);
        if (enemy != nullptr && enemy->getIsGuardian()) {
            hasProtectors = true;
        }
    }
    setIsProtected(hasProtectors); // ie: is surrounding dragons dead, item isn't protected anymore
}
