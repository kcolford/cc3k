#include "Floor.hh"
#include "GameObject.hh"
#include "SceneGraph.hh"
#include "CollectComponent.hh"
#include "Game.hh"
#include "collision_masks.hh"

struct WinGame: CollectComponent {
  void collectMe(GameObject &me __attribute__((__unused__)),
                 GameObject &collector __attribute__((__unused__))) {
    game.beatlevel();
  }
};

static shared_ptr<WinGame> win = make_shared<WinGame>();

GameObjectPtr make_stairs()
{
  GameObjectPtr out = make_shared<GameObject>();
  out->collect = win;
  out->scene = make_scene_graph('\\');
  out->collision_mask = COLL_DOOR;
  return out;
}
