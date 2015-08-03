#include "GameObject.hh"
#include "Game.hh"
#include "Floor.hh"
#include "Controller.hh"
#include "Potion.hh"
#include "Enemy.hh"
#include "CollectComponent.hh"
#include "Character.hh"
#include "collision_masks.hh"
#include "Gold.hh"
#include <boost/foreach.hpp>

GameObject::GameObject()
  : collision_mask(0)
  , x_(0)
  , y_(0)
{}

void GameObject::update()
{
  if (controller)
    controller->update(*this);
  if (stats)
    stats->update();
}

void GameObject::use_potion(Character &target)
{
  if (potion_use) {
    game.stats.action << "PC uses " << name << ". ";
    potion_use->apply(target);
    kill();
  }
}

bool GameObject::setPos(int x, int y)
{
  BOOST_FOREACH(GameObjectPtr o, game.floor()->cells[x][y])
    if (collision_mask & o->collision_mask)
      return true;

  GameObjectPtr myself = shared_from_this();
  game.floor()->cells[x_][y_].erase(myself);

  BOOST_FOREACH(GameObjectPtr o, game.floor()->cells[x][y]) {
    if (o->collect) {
      o->collect->collectMe(*o, *this);
    }
  }

  x_ = x;
  y_ = y;
  game.floor()->cells[x_][y_].insert(myself);
  if (scene)
    scene->update(x_, y_);

  return false;
}

GameObjectPtr make_basic_object(char type)
{
  GameObjectPtr out = make_shared<GameObject>();
  out->scene = make_scene_graph(type);
  return out;
}

static GameObjectPtr make_object_from_encoding(char type)
{
  switch (type) {
  case '\\': return make_stairs();
  case '@': return game.player();
  case '0': return make_potion(EFFECT_HEALTH, 10);
  case '1': return make_potion(EFFECT_BUFF_ATK, 5);
  case '2': return make_potion(EFFECT_BUFF_DEF, 5);
  case '3': return make_potion(EFFECT_DAMAGE, 10);
  case '4': return make_potion(EFFECT_NERF_ATK, 5);
  case '5': return make_potion(EFFECT_NERF_DEF, 5);
  case '6': return make_gold(PILE_NORMAL);
  case '7': return make_gold(PILE_SMALL);
  case '8': return make_gold(PILE_MERCHANT);
  case '9': return make_gold(PILE_DRAGON);
  default: return make_enemy(type);
  case 0: return make_shared<GameObject>();
  }
}

GameObjectPtr make_object(char type)
{
  GameObjectPtr out = make_object_from_encoding(type);
  if (out->scene)
    game.floor()->scene->sub(out->scene);
  return out;
}

int GameObject::getX()
{
  return x_;
}

int GameObject::getY()
{
  return y_;
}

void GameObject::kill()
{
  scene.reset();
  potion_use.reset();
  collect.reset();
  controller.reset();

  name.clear();
  collision_mask = COLL_NOTHING;
  stats.reset();
}

int GameObject::get_attacked(Character &attacker)
{
  assert(stats);
  controller->get_attacked(attacker);
  int dmg = stats->get_attacked(attacker);
  if (stats->health() <= 0) {
    stats->died(*this);
    kill();
  }
    
  return dmg;
}
