#include <sstream>
#include "merchant.h"

#include "player.h"


Merchant::Merchant(int maxHealth, int attack, int defence, std::string race) : Enemy{maxHealth, attack, defence, race}{
    // setAbilityType(AbilityType::ActiveAbility);
};

char Merchant::getSymbol() {
    return 'M';
}
