#include "Gold.hh"
#include "CollectGold.hh"
#include "SceneGraph.hh"
#include "collision_masks.hh"
#include "CollectComponent.hh"
#include "Game.hh"
#include "Character.hh"
#include "GameObject.hh"

CollectGold::CollectGold(int g)
  : mygold(g)
{}

void CollectGold::collectMe(GameObject &me, Character &collector)
{
  mygold += mygold * collector.score_bonus();
  collector.gold(collector.gold() + mygold);
  game.stats.action << "The PC picks up " << mygold << " gold. ";
  me.kill();
}

GameObjectPtr make_gold(gold_type amount)
{
  GameObjectPtr out = make_basic_object('G');
  out->collect = make_shared<CollectGold>(amount);
  out->collision_mask = COLL_DOOR;
  return out;
}
