#include "Player.hh"
#include "Game.hh"
#include "Character.hh"
#include "collision_masks.hh"
#include "GameObject.hh"
#include "View.hh"
#include "PlayerInputController.hh"

GameObjectPtr make_player(std::string cls)
{
  switch (cls[0]) {
#define D(C, CLASS)                             \
    case C: cls = CLASS; break
    D('s', "shade");
    D('d', "drow");
    D('v', "vampire");
    D('t', "troll");
    D('g', "goblin");
#undef D
  default:
    throw 0;
  }

  game.stats.race = cls;

  GameObjectPtr o = make_shared<GameObject>();
  o->controller = make_shared<PlayerInputController>();
  o->stats = make_shared<Character>(character_map.find(cls)->second);
  o->collision_mask = COLL_PLAYER | COLL_WALL;
  o->scene = make_scene_graph('@');
  o->name = "themself";
  return o;
}

GameObjectPtr player()
{
  return game.player();
}
