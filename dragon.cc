#include <sstream>
#include "dragon.h"

#include "player.h"


Dragon::Dragon(int maxHealth, int attack, int defence, std::string race) : Enemy{maxHealth, attack, defence, race}{
    // setAbilityType(AbilityType::ActiveAbility);
};

char Dragon::getSymbol() {
    return 'D';
}
