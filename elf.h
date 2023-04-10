#ifndef _ELF_H_
#define _ELF_H_

#include "player.h"

class Elf : public Player {
    public:
        Elf(int maxHealth=140, int attack=30, int defence=10, std::string race="Elf");
};

#endif
