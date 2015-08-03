#include "PlayerInputController.hh"
#include "Character.hh"
#include "Game.hh"
#include "GameObject.hh"
#include "View.hh"
#include "within_one_block.hh"
#include <iostream>
#include <utility>
#include <boost/foreach.hpp>
#include <boost/container/flat_map.hpp>

template<typename K, typename V>
struct map: boost::container::flat_map<K, V>
{};

static map<std::string, std::pair<int, int> > make_dir_map()
{
  using std::make_pair;
  map<std::string, std::pair<int, int> > m;
  m["no"] = make_pair(0, 1);
  m["so"] = make_pair(0, -1);
  m["ea"] = make_pair(1, 0);
  m["we"] = make_pair(-1, 0);
  m["ne"] = make_pair(1, 1);
  m["nw"] = make_pair(-1, 1);
  m["se"] = make_pair(1, -1);
  m["sw"] = make_pair(-1, -1);
  return m;
}

static map<std::string, std::pair<int, int> > directions = make_dir_map();

static map<std::string, std::string> make_message_map()
{
  map<std::string, std::string> m;
  m["no"] = "North";
  m["so"] = "South";
  m["ea"] = "East";
  m["we"] = "West";
  m["ne"] = "North-East";
  m["nw"] = "North-West";
  m["se"] = "South-East";
  m["sw"] = "South-West";
  return m;
}

static map<std::string, std::string> dir_messages = make_message_map();

void PlayerInputController::update(GameObject &me)
{
  std::string cmd = game.view->get_event();
  if (cmd == "") {
    game.stats.action << "The PC got distracted and didn't do anything. ";
    game.no_turn_loss();
  } else if (cmd == "q")
    game.quit();
  else if (cmd == "r")
    game.restart();
  else if (cmd == "a") {
    std::string dir = game.view->get_event();
    int tx = me.x() + directions[dir].first;
    int ty = me.y() + directions[dir].second;
    bool hit_something = false;
    BOOST_FOREACH(GameObjectPtr p, floor()->cells[tx][ty]) {
      if (p->controller && p->stats) {
        hit_something = true;
        int dmg = p->get_attacked(*me.stats);
        if (p->stats) {
          game.stats.action << "PC deals " << dmg << " damage to " << p->name << " (" << p->stats->health() << " HP). ";
        } else {
          game.stats.action << "The PC dealt " << dmg << " damage, killing their foe. ";
        }
      }
    }
    if (!hit_something) {
      game.stats.action << "The PC missed! ";
      game.no_turn_loss();
    }
  } else if (cmd == "u") {
    std::string dir = game.view->get_event();
    int tx = me.x() + directions[dir].first;
    int ty = me.y() + directions[dir].second;
    bool got_a_potion = false;
    BOOST_FOREACH(GameObjectPtr p, floor()->cells[tx][ty]) {
      if (p->potion_use) {
        got_a_potion = true;
        used_potions.insert(p->name);
        p->use_potion(*me.stats);
      }
    }
    if (!got_a_potion) {
      game.stats.action << "The PC couldn't find a potion there. ";
      game.no_turn_loss();
    }
  } else if (directions.count(cmd)) {
    std::string &dir = cmd;
    if (me.setPos(me.x() + directions[dir].first,
                  me.y() + directions[dir].second)) {
      game.stats.action << "PC tried to move " << dir_messages[dir] << " but was stopped. ";
      game.no_turn_loss();
    } else {
      game.stats.action << "PC moves " << dir_messages[dir] << ". ";
      for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
          BOOST_FOREACH(GameObjectPtr p,
                        floor()->cells[me.x() + i][me.y() + j]) {
            if (p->potion_use) {
              if (used_potions.count(p->name))
                game.stats.action << "The PC sees a vial of " << p->name << ". ";
              else
                game.stats.action << "The PC sees an unknown potion. ";
            }
          }
        }
      }

    }
  } else {
    game.stats.action << "The PC shouts out \"" << cmd << "!!!\" and does nothing else. ";
    game.no_turn_loss();
  }
}

PlayerInputController::~PlayerInputController() {
  game.game_over();
}

