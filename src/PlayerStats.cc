#include "PlayerStats.hh"
#include "Game.hh"
#include "GameObject.hh"
#include "Character.hh"

int PlayerStats::gold()
{
  return game.player()->stats->gold();
}

int PlayerStats::floor()
{
  return game.currentlevel();
}

int PlayerStats::health()
{
  return game.player()->stats->health();
}

int PlayerStats::def()
{
  return game.player()->stats->def();
}

int PlayerStats::atk()
{
  return game.player()->stats->atk();
}
