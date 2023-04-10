#include <sstream>
#include "troll.h"

#include "player.h"


Troll::Troll(int maxHealth, int attack, int defence, std::string race) : Enemy{maxHealth, attack, defence, race}{
    setAbilityType(AbilityType::ActiveAbility);
};

char Troll::getSymbol() {
    return 'T';
}

std::string Troll::attack(Player* p) {
    std::ostringstream o;
    o << Enemy::attack(p);
    o << specialAbility(p);
    return o.str();
}

std::string Troll::specialAbility(Player* p) {
    // Active abilities demand non-null player, so only activated when attacking PC

    // Health regen for Trolls (activated on random)

    if (!p->isDead() && (getHealth() != getMaxHealth())) {
        std::ostringstream o;
        int healthRegen = 8;
        int currentHealth = getHealth();
        currentHealth += healthRegen;
        if (currentHealth < getMaxHealth()) currentHealth = getMaxHealth();
        setHealth(currentHealth);

        o << getSymbol() << " regenerated " << healthRegen << " health.";
        return o.str();

    } else {
        return "";
    }
}
