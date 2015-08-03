#ifndef POTION_HH
#define POTION_HH

#include "GameObject.hh"

class Character;

enum effect_type {
  EFFECT_NONE = 0,
  EFFECT_HEALTH = 0x1,
  EFFECT_ATK  = 0x2,
  EFFECT_DEF  = 0x4,
  EFFECT_NEGATIVE = 0x10000,
  EFFECT_EXTENDED = 0x20000,
  
  EFFECT_DAMAGE   = EFFECT_NEGATIVE | EFFECT_HEALTH,
  EFFECT_BUFF_ATK = EFFECT_EXTENDED | EFFECT_ATK,
  EFFECT_NERF_ATK = EFFECT_EXTENDED | EFFECT_NEGATIVE | EFFECT_ATK,
  EFFECT_BUFF_DEF = EFFECT_EXTENDED | EFFECT_DEF,
  EFFECT_NERF_DEF = EFFECT_EXTENDED | EFFECT_NEGATIVE | EFFECT_DEF,
};

class Potion
{
public:
  Potion(effect_type effect, int amount);

private:
  effect_type effect_;
  int amount_;

public:
  class Modifier
  {
  public:
    Modifier();
    Modifier(Character &p, effect_type effect, int amount);
    ~Modifier();
    Modifier(const Modifier &other);
    Potion::Modifier &operator=(Modifier other);

  private:
    Character *p_;
    effect_type effect_;
    int amount_;
  };

  void apply(Character &p);

};

GameObjectPtr make_potion(effect_type effect, int amount);

#endif
