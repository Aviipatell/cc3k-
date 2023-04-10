#include <sstream>
#include "vampire.h"

#include "player.h"


Vampire::Vampire(int maxHealth, int attack, int defence, std::string race) : Enemy{maxHealth, attack, defence, race}{
    setAbilityType(AbilityType::ActiveAbility);
    
};

char Vampire::getSymbol() {
    return 'V';
}

std::string Vampire::attack(Player* p) {
    std::ostringstream o;
    o << Enemy::attack(p);
    o << specialAbility(p);
    return o.str();
}

std::string Vampire::specialAbility(Player* p) {
    // Active abilities demand non-null player, so only activated when attacking PC

    // Health Stealing for Vampire

    if (!p->isDead()) {
        std::ostringstream o;
        int healthStolen = 1;
        p->setHealth(p->getHealth() - 1);
        int currentHealth = getHealth();
        currentHealth += healthStolen;
        if (currentHealth > getMaxHealth()) currentHealth = getMaxHealth();
        setHealth(currentHealth);

        o << getSymbol() << " stole some health from PC.";
        return o.str();

    } else {
        return "";
    }
}
