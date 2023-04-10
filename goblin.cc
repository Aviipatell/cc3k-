#include <sstream>
#include "goblin.h"

#include "player.h"


Goblin::Goblin(int maxHealth, int attack, int defence, std::string race) : Enemy{maxHealth, attack, defence, race}{
    setAbilityType(AbilityType::ActiveAbility);
};

char Goblin::getSymbol() {
    return 'N';
}

std::string Goblin::attack(Player* p) {
    std::ostringstream o;
    o << Enemy::attack(p);
    o << specialAbility(p);
    return o.str();
}

std::string Goblin::specialAbility(Player* p) {
    // Active abilities demand non-null player, so only activated when attacking PC

    // Gold Stealing for Goblin

    if (!p->isDead()) {
        std::ostringstream o;
        int goldStolen = 1;
        double currentPlayerGold = p->getPlayerGold();
        currentPlayerGold -= goldStolen;
        if (currentPlayerGold < 0) currentPlayerGold = 0;
        p->setPlayerGold(currentPlayerGold);

        o << getSymbol() << " stole some gold from PC.";
        return o.str();

    } else {
        return "";
    }
}
