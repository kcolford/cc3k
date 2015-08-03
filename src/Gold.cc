#include "Gold.hh"
#include "CollectGold.hh"
#include "SceneGraph.hh"
#include "collision_masks.hh"
#include "CollectComponent.hh"
#include "Game.hh"
#include "Character.hh"

CollectGold::CollectGold(int g)
  : mygold(g)
{}

void CollectGold::collectMe(GameObject &me, GameObject &collector)
{
  if (collector.stats) {
    mygold += mygold * collector.stats->score_bonus();
    collector.stats->gold(collector.stats->gold() + mygold);
    game.stats.action << "The PC picks up " << mygold << " gold. ";
  }
  me.kill();
}

GameObjectPtr make_gold(gold_type amount)
{
  GameObjectPtr out = make_basic_object('G');
  out->collect = make_shared<CollectGold>(amount);
  out->collision_mask = COLL_DOOR;
  return out;
}
