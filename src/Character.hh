#ifndef CHARACTER_HH
#define CHARACTER_HH

#include <map>
#include <string>

class GameObject;

class Character
{
public:

  Character();

  enum faction_type {
    FACTION_ENEMY,
    FACTION_MERCHANT,
    FACTION_FRIENDLY,
  };

#define DECLARE_MEMBER(TYPE, ID)                \
private:                                        \
  TYPE ID ## _;                                 \
public:                                         \
 TYPE ID() const                                \
  { return ID ## _; }                           \
 Character &ID(TYPE arg)                        \
  { ID ## _ = arg; return *this; }

  DECLARE_MEMBER(int, health)
  DECLARE_MEMBER(int, atk)
  DECLARE_MEMBER(int, def)
  DECLARE_MEMBER(int, gold)

  DECLARE_MEMBER(faction_type, faction)
  DECLARE_MEMBER(bool, is_player)
  DECLARE_MEMBER(int, max_hp)
  DECLARE_MEMBER(float, potion_bonus)
  DECLARE_MEMBER(int, life_steal)
  DECLARE_MEMBER(int, capped_regen)
  DECLARE_MEMBER(int, looting)
  DECLARE_MEMBER(float, score_bonus)
  DECLARE_MEMBER(int, garlic_skin)
  DECLARE_MEMBER(bool, weakness_to_garlic)
  DECLARE_MEMBER(float, dodge)
  DECLARE_MEMBER(float, goblin_bane)
  DECLARE_MEMBER(int, weakness_to_goblin_bane)
  DECLARE_MEMBER(int, extra_hits)
  DECLARE_MEMBER(int, resist_extra_hits)
  DECLARE_MEMBER(bool, is_neutral)

#undef DECLARE_MEMBER

  int get_attacked(Character &attacker);
  void update();
  void died(GameObject &me);

};

extern std::map<std::string, Character> character_map;

#endif
