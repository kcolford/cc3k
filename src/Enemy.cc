#include "Enemy.hh"
#include "Controller.hh"
#include "GameObject.hh"
#include "Game.hh"
#include "Character.hh"
#include "SceneGraph.hh"
#include "collision_masks.hh"
#include "DragonAI.hh"
#include "main.hh"
#include "Player.hh"
#include <cstdlib>
#include <cctype>

bool within_one_block(const GameObject &l, const GameObject &r)
{
  if (config["advanced_game"])
    return ((abs(l.x() - r.x()) <= 1 && l.y() == r.y()) ||
            (abs(l.y() - r.y()) <= 1 && l.x() == r.x()));
  else
    return abs(l.x() - r.x()) <= 1 && abs(l.y() - r.y()) <= 1;
}

static const int max_iteration = 8;

struct EnemyAI: Controller {
  void get_attacked(const Character &attacker)
  { is_hostile = true; }
  bool is_hostile;
  EnemyAI(bool hos = true): is_hostile(hos) {}
  void update(GameObject &me) {
    if (is_hostile && within_one_block(me, *player())) {
      int dmg = player()->get_attacked(*me.stats);
      game.stats.action << me.name << " deals " << dmg << " damage to PC. ";
    } else {
      int xoff, yoff;
      for (int i = 0; i < max_iteration; i++) {
        xoff = (int) (3 * r()) - 1;
        yoff = (int) (3 * r()) - 1;
        if ((config["advanced_game"] ? abs(xoff) + abs(yoff) <= 1
                                     : (xoff || yoff))
            && !me.setPos(me.x() + xoff, me.y() + yoff))
          break;
      }
    }
  }
};

static shared_ptr<EnemyAI> e_ai = make_shared<EnemyAI>();
static shared_ptr<EnemyAI> mer_ai = make_shared<EnemyAI>(false);

GameObjectPtr make_enemy(char type) {
  std::string cls;
  switch (std::tolower(type)) {
#define D(C, CLASS)                             \
    case C: cls = CLASS; break
    D('h', "human");
    D('w', "dwarf");
    D('e', "elf");
    D('o', "orcs");
    D('m', "merchant");
    D('l', "halfling");
    D('d', "dragon");
#undef D
  default:
    throw 0;
  }

  GameObjectPtr out = make_basic_object(std::toupper(type));
  out->stats = make_shared<Character>(character_map.find(cls)->second);
  cls[0] = toupper(cls[0]);
  out->name = cls;
  switch (std::tolower(type)) {
  case 'd': out->controller = make_shared<DragonAI>(GameObjectPtr()); break;
  case 'm': out->controller = mer_ai;                                 break;
  default:  out->controller = e_ai;                                   break;
  }
  out->collision_mask = (COLL_DOOR | COLL_PASSAGE | COLL_PLAYER |
                         COLL_STAIRS | COLL_WALL);
  return out;
}


DragonAI::DragonAI(GameObjectPtr g)
  : guarding(g)
{ guarding->collision_mask |= COLL_PLAYER; }
  
DragonAI::~DragonAI()
{ guarding->collision_mask &= ~COLL_PLAYER; }

void DragonAI::update(GameObject &me)
{
  if (within_one_block(*player(), me) ||
      within_one_block(*player(), *guarding)) {
    int dmg = player()->get_attacked(*me.stats);
    game.stats.action << "The Dragon defends its hoard, dealing " << dmg << " damage. ";
  }
}

GameObjectPtr make_dragon(GameObjectPtr guarding)
{
  GameObjectPtr out = make_enemy('d');
  assert(out);
  assert(out->controller);
  DragonAI &d = dynamic_cast<DragonAI &>(*out->controller);
  d.guarding = guarding;
  return out;
}
