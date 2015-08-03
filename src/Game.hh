#ifndef GAME_HH
#define GAME_HH

// FIXME: these headers are edited frequently yet this file is
//        included everywhere, compilation time could be reduced with
//        PreCompiled headers or setting up forward declarations only
//        here.
#include "shared_ptr.hh"
#include "GameObjectPtr.hh"
#include "SceneGraph.hh"
#include "Floor.hh"
#include "PlayerStats.hh"
#include <list>
#include <sstream>

class View;

class Game
{
private:
  // The main loop of the game.
  void mainloop();

public:

  Game();

  // Fill in the floor with random enemies.
  void fillFloor();

  // Run the main loop of the whole game.
  void run();

  // Restart the game.
  void restart();

  // Quit the game.
  void quit();

  // We have won the level.
  void beatlevel();

  // Fetch the player character.
  GameObjectPtr player()
  { return player_; }

  // Fetch the current floor.
  FloorPtr floor()
  { return floor_; }

  // Signal the end of the game.
  void game_over();

  // Return the current level of the game.
  int currentlevel() const
  { return currentlevel_; }

  SceneGraphPtr scene;             // The current scene.

  void setIn(std::istream &i);
  void setIn(std::string s);

  void no_turn_loss();

private:
  bool game_is_playing;
  GameObjectPtr player_;        // The player's character.
  FloorPtr floor_;              // The current floor.
  int currentlevel_;

  std::string in;

public:
  shared_ptr<View> view;

public:
  PlayerStats stats;

};

extern Game game;

// Return a random number in the range [0, 1)
double r();


#endif
