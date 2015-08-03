#include "PlayerStats.hh"
#include "Game.hh"
#include "GameObject.hh"
#include "Player.hh"
#include "Character.hh"

int PlayerStats::gold()
{
  return player()->stats->gold();
}

int PlayerStats::floor()
{
  return game.currentlevel();
}

int PlayerStats::health()
{
  return player()->stats->health();
}

int PlayerStats::def()
{
  return player()->stats->def();
}

int PlayerStats::atk()
{
  return player()->stats->atk();
}
