#include <sstream>
#include "phoenix.h"

#include "player.h"


Phoenix::Phoenix(int maxHealth, int attack, int defence, std::string race) : Enemy{maxHealth, attack, defence, race}{
    setAbilityType(AbilityType::ActiveAbility);
};

char Phoenix::getSymbol() {
    return 'X';
}

std::string Phoenix::attack(Player* p) {
    std::ostringstream o;
    if (getHasAbility()) {
        o << specialAbility(p);
    }
    if (!isDead()) {
        o << Enemy::attack(p);
    }
    return o.str();
}

std::string Phoenix::specialAbility(Player* p) {
    // Active abilities demand non-null player, so only activated when attacking PC

    // Desperate rage for Phoenix

    if (!p->isDead() && getHealth() <= 10) {
        std::ostringstream o;
        int playerHealth = p->getHealth();
        int damage = p->getHasBarrierSuit() ? getMaxHealth() / 2 : getMaxHealth();
        playerHealth -= damage;
        if (playerHealth < 0) playerHealth = 0;
        p->setHealth(playerHealth);
        setHealth(0); // kill the pheonix

        o << getSymbol() << " exploded in rage. It killed itself, and dealt PC " << damage << " damage.";
        return o.str();
    } else {
        return "";
    }
}
