#include "Character.hh"
#include "shared_ptr.hh"
#include "Game.hh"
#include "GameObject.hh"
#include "Gold.hh"
#include "collision_masks.hh"
#include "CollectComponent.hh"
#include <cstring>
#include <limits>

Character::Character()
{
  memset(this, 0, sizeof *this);
}

static
std::map<std::string, Character> make_mapping()
{
  std::map<std::string, Character> m;

#define D(CLASS, HEALTH, ATK, DEF)                              \
  m[#CLASS].health(HEALTH).max_hp(HEALTH).atk(ATK).def(DEF)
#define DP(...) D(__VA_ARGS__).dodge(.5)

  DP(shade, 125, 25, 25).score_bonus(.5);
  DP(drow, 150, 25, 15).potion_bonus(.5).resist_extra_hits(1);
  DP(vampire, 50, 25, 25).life_steal(5).weakness_to_garlic(1);
  DP(troll, 120, 25, 15).capped_regen(5);
  DP(goblin, 110, 15, 20).looting(5).weakness_to_goblin_bane(1);

  D(human, 140, 20, 20).gold(2 * PILE_NORMAL);
  D(dwarf, 100, 20, 30).garlic_skin(10);
  D(elf, 140, 30, 10).extra_hits(1);
  D(orcs, 180, 30, 25).goblin_bane(.5);
  D(merchant, 30, 70, 5).gold(PILE_MERCHANT);
  D(dragon, 150, 20, 20);
  D(halfling, 100, 15, 20).dodge(.5);

#undef DP
#undef D

  return m;
}

std::map<std::string, Character> character_map = make_mapping();

void Character::update()
{
  health(std::max(health(), std::min(health() + capped_regen(), max_hp())));
}

int Character::get_attacked(Character &attacker)
{
  int total_damage = 0;
  for (int i = 0; i < std::max(attacker.extra_hits() -
                               resist_extra_hits(), 1); i++) {
    int dmg = 0.5 + ((100.0 / (100.0 + def())) * attacker.atk());
    dmg *= 1.0 + (weakness_to_goblin_bane() * attacker.goblin_bane());
    if (r() < dodge())
      dmg = 0;
    if (dmg) {
      attacker.health(attacker.health() + attacker.life_steal());
      if (attacker.weakness_to_garlic())
        attacker.health(attacker.health() - garlic_skin());
    }
    total_damage += dmg;
  }
  health(health() - total_damage);
  if (health() <= 0)
    attacker.gold(attacker.gold() + attacker.looting());
#if 1
  if (max_hp() == 180) {
    game.stats.action << "The orc recieved " << total_damage << " damage. ";
  }
#endif
  return total_damage;
}

void Character::died(GameObject &me)
{
  me.collision_mask = COLL_NOTHING;
  if (gold() == 0) {
    GameObjectPtr p = make_object('6' + 2 * r());
    p->collect->collectMe(*p, *game.player());
  } else {
    GameObjectPtr o = make_gold((gold_type) gold());
    game.floor()->scene->sub(o->scene);
    o->setPos(me.x(), me.y());
  }
}

