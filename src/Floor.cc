#include "Floor.hh"
#include "SceneGraph.hh"
#include "smart_ptr.hh"
#include "GameObject.hh"
#include "Game.hh"
#include "collision_masks.hh"
#include "SceneGraph.hh"
#include "Player.hh"
#include <sstream>
#include <boost/foreach.hpp>
#include <cstring>
#include <iostream>

Floor::Floor()
  : is_filled(false)
{
  scene = make_scene_graph(0);
  cell_graph = make_scene_graph(0);
  scene->sub(cell_graph);
}

GameObjectPtr Floor::make_cell(char type)
{
  GameObjectPtr out = make_shared<GameObject>();

  switch (type) {
#define SET_COLLISION(TYPE, MASK)                       \
    case TYPE:                                          \
      out->scene = make_scene_graph(TYPE);              \
      out->collision_mask = MASK;                       \
      break;
    SET_COLLISION('|', COLL_WALL);
    SET_COLLISION('-', COLL_WALL);
    SET_COLLISION('+', COLL_DOOR);
    SET_COLLISION(' ', COLL_EVERYTHING);
    SET_COLLISION('#', COLL_PASSAGE);
  default:
    SET_COLLISION('.', COLL_OPEN_FLOOR);
#undef SET_COLLISION
  }
  cell_graph->sub(out->scene);
  return out;
}

void Floor::init(std::istream &in)
{
  assert(floor() == shared_from_this());
  scene->sub(player()->scene);
  std::string line;
  for (int y = height - 1; y >= 0 && getline(in, line); y--) {
    for (int x = 0; x < width && x < line.size(); x++) {
      make_cell(line[x])->setPos(x, y);
      if (!std::strchr("|-+ #.", line[x])) {
        is_filled = true;
        make_object(line[x])->setPos(x, y);
      }
    }
  }
}

void Floor::init(std::string str)
{
  std::istringstream ss(str);
  init(ss);
}

FloorPtr make_floor()
{
  FloorPtr out = make_shared<Floor>();
  return out;
}

unsigned Floor::collision_mask(int x, int y)
{
  unsigned out = 0;
  BOOST_FOREACH(GameObjectPtr o, cells[x][y])
    out |= o->collision_mask;
  return out;
}

FloorPtr floor()
{
  return game.floor();
}
