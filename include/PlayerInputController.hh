#ifndef PLAYERINPUTCONTROLLER_HH
#define PLAYERINPUTCONTROLLER_HH

#include "Controller.hh"
#include <set>
#include <string>

class PlayerInputController
  : public Controller
{
  std::set<std::string> used_potions;
  void update(GameObject &me);
public:
  ~PlayerInputController();
};

#endif
