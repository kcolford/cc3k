#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include "smart_ptr.hh"
#include "GameObjectPtr.hh"
#include <utility>

struct SceneGraph;
struct Potion;
struct CollectComponent;
struct Character;
struct Controller;

struct GameObject
  : enable_shared_from_this<GameObject>
{
  GameObject();

  std::string                  name;
  shared_ptr<SceneGraph>       scene;
  shared_ptr<Potion>           potion_use;
  shared_ptr<CollectComponent> collect;
  shared_ptr<Character>        stats;
  shared_ptr<Controller>       controller;
  unsigned collision_mask : 32;

  bool operator==(const GameObject &other);
  
  // Set the position of this object to (x, y) and return true if
  // there was something already there and so this object could not be
  // moved.
  bool setPos(int x, int y);
  bool setPos(std::pair<int, int> xy)
  { return setPos(xy.first, xy.second); }

  void update();
  void use_potion(Character &target);
  int get_attacked(Character &attacker);
  void kill();
  
  int getX();
  int getY();

  int x() const
  { return x_; }
  int y() const
  { return y_; }

private:
  int x_;
  int y_;

};

#endif
