#ifndef __STATUS_EFFECT_H_
#define __STATUS_EFFECT_H_

class Player;

class StatusEffect {
    Player *p;
public:
    virtual void applyEffect(Player &p) = 0;
};

class HealthEffect: public StatusEffect {
    int quantity;
public:
    void applyEffect(PLayer &p) override;
};

class AttackEffect: public StatusEffect {
    int quantity;
public:
    void applyEffect(PLayer &p) override;
};

class DefenceEffect: public StatusEffect {
    int quantity;
public:
    void applyEffect(PLayer &p) override;
};

#endif
