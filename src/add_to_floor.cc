#include "add_to_floor.hh"
#include "Floor.hh"
#include "SceneGraph.hh"
#include "GameObject.hh"

bool add_to_floor(GameObjectPtr o, int x, int y)
{
  floor()->scene->sub(o->scene);
  return o->setPos(x, y);
}
