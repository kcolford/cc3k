#ifndef PLAYERINPUTCONTROLLER_HH
#define PLAYERINPUTCONTROLLER_HH

#include "Controller.hh"
#include <set>
#include <string>

class PlayerInputController
  : public Controller
{
  std::set<std::string> used_potions;
  friend void player_used_potion(std::string name);
  void update(GameObject &me);
public:
  ~PlayerInputController();
};

#endif
