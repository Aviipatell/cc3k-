#include <sstream>
#include "werewolf.h"

#include "player.h"


Werewolf::Werewolf(int maxHealth, int attack, int defence, std::string race) : Enemy{maxHealth, attack, defence, race}{
    // setAbilityType(AbilityType::ActiveAbility);
};

char Werewolf::getSymbol() {
    return 'W';
}

// std::string Werewolf::specialAbility(Player* p) {
//
// }
