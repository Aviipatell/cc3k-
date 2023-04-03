#ifndef __DRAGON_HOARD_H_
#define __DRAGON_HOARD_H_

#include "protected_item.h"

class DragonHoard: public ProtectedItem {
public:
    void useItem() override;
};

#endif