#ifndef PLAYERSTATS_HH
#define PLAYERSTATS_HH

#include <string>
#include <sstream>

struct PlayerStats {
  std::string race;
  int gold();
  int floor();
  int health();
  int atk();
  int def();
  std::stringstream action;
};

#endif
