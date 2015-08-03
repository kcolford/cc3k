#ifndef FLOOR_HH
#define FLOOR_HH

#include "smart_ptr.hh"
#include "SceneGraph.hh"
#include "GameObjectPtr.hh"
#include "Potion.hh"
#include <istream>
#include <list>
#include <set>
#include <vector>
#include <string>

struct Floor
  : enable_shared_from_this<Floor>
{
  static const int width = 79;
  static const int height = 25;

  SceneGraphPtr scene;
  SceneGraphPtr cell_graph;

  std::set<GameObjectPtr> cells[width][height];
  std::list<Potion::Modifier> modifications;

  unsigned collision_mask(int x, int y);

  void init(std::istream &in);
  void init(std::string str);

  bool is_filled;

  Floor();

private:
  GameObjectPtr make_cell(char type);

};

typedef shared_ptr<Floor> FloorPtr;

FloorPtr make_floor();
GameObjectPtr make_stairs();
FloorPtr floor();               // game.floor()

#endif
