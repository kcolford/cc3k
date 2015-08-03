#include "Game.hh"
#include "Floor.hh"
#include "GameObject.hh"
#include "Character.hh"
#include "SceneGraph.hh"
#include "Player.hh"
#include "View.hh"
#include "make_view.hh"
#include "FloorFiller.hh"
#include <queue>
#include <sstream>
#include <exception>
#include <boost/foreach.hpp>

static const char *default_floorplan = "\
|-----------------------------------------------------------------------------|\n\
|                                                                             |\n\
| |--------------------------|        |-----------------------|               |\n\
| |..........................|        |.......................|               |\n\
| |..........................+########+.......................|-------|       |\n\
| |..........................|   #    |...............................|--|    |\n\
| |..........................|   #    |..................................|--| |\n\
| |----------+---------------|   #    |----+----------------|...............| |\n\
|            #                 #############                |...............| |\n\
|            #                 #     |-----+------|         |...............| |\n\
|            #                 #     |............|         |...............| |\n\
|            ###################     |............|   ######+...............| |\n\
|            #                 #     |............|   #     |...............| |\n\
|            #                 #     |-----+------|   #     |--------+------| |\n\
|  |---------+-----------|     #           #          #              #        |\n\
|  |.....................|     #           #          #         |----+------| |\n\
|  |.....................|     ########################         |...........| |\n\
|  |.....................|     #           #                    |...........| |\n\
|  |.....................|     #    |------+--------------------|...........| |\n\
|  |.....................|     #    |.......................................| |\n\
|  |.....................+##########+.......................................| |\n\
|  |.....................|          |.......................................| |\n\
|  |---------------------|          |---------------------------------------| |\n\
|                                                                             |\n\
|-----------------------------------------------------------------------------|\n\
";

Game game;

struct Restart {};
void Game::restart() { if (game_is_playing) throw Restart(); }

struct Quit {};
void Game::quit() { if (game_is_playing) throw Quit(); }

struct BeatLevel {};
void Game::beatlevel() { if (game_is_playing) throw BeatLevel(); }

struct GameOver {};
void Game::game_over() { if (game_is_playing) throw GameOver(); }

static const int max_level = 5;

Game::Game()
  : scene(make_scene_graph(0))
  , game_is_playing(false)
{
  std::stringstream ss;
  for (int i = 0; i < max_level; i++)
    ss << default_floorplan;
  setIn(ss.str());
}

void Game::setIn(std::istream &in)
{
  in >> std::noskipws;
  std::string s(std::istream_iterator<char>(in),
                (std::istream_iterator<char>()));
  setIn(s);
}

void Game::setIn(std::string s)
{
  in = s;
}

static const int hud_height = 5;

struct NoTurnLoss {};
void Game::no_turn_loss() { if (game_is_playing) throw NoTurnLoss(); }

void Game::mainloop()
{
  struct InPlay {
    bool &flag;
    InPlay(bool &f): flag(f) {
      flag = true;
    }
    ~InPlay() {
      flag = false;
    }
  } playing_status(game_is_playing);
  
  player_ = make_player(view->get_user_input("Are you a Shade, Drow, Vampire, Troll, or Goblin?"));

  scene = make_scene_graph(0);

  for (currentlevel_ = 1; currentlevel_ <= max_level; currentlevel_++) {
    floor_ = make_floor();
    game.scene->sub(floor()->scene);
    floor()->init(in);
    fillFloor();
    try {
      // Do an initial update of the view to make sure the screen
      // shows.
      view->update(*this);

      while (true) {
        try {
          view->poll_input();

          player()->update();
          
          // Now we update all the entities that have controllers by
          // first sticking them all into a queue and then exhausting
          // that queue.
          std::vector<GameObjectPtr> q;
          q.reserve(100);
          for (int y = Floor::height - 1; y >= 0; y--)
            for (int x = 0; x < Floor::width; x++) {
              BOOST_FOREACH(GameObjectPtr e, floor()->cells[x][y])
                if (e != player() && e->controller)
                  q.push_back(e);
            }
          
          BOOST_FOREACH(GameObjectPtr e, q)
            e->update();

        } catch (NoTurnLoss ntl) {
          ;                     // do nothing
        }

        // Finally we update the view object.
        view->update(*this);
      }
    } catch (BeatLevel b) {
      // We be the level!
    }
  }
}

struct EOFError {};

void Game::run()
{
  if (!view)
    view = make_view();

  // Reset all of the game's state.
  floor_.reset();
  player_.reset();
  scene.reset();
  stats.race = "";
  stats.action.str("");

  try {
    mainloop();
  } catch (Restart r) {
    run();
  } catch (GameOver g) {
    std::stringstream ss;
    ss << "Game Over." << std::endl << "Score: " << game.stats.gold() << std::endl;
    view->big_notification(ss);
    run();
  } catch (Quit q) {
    return;
  } catch (EOFError e) {
    return;
  }

  std::stringstream ss;
  ss << "You Win!!" << std::endl << "Score: " << stats.gold();
  view->big_notification(ss);

}

void Game::fillFloor()
{
  if (!floor()->is_filled)
    FloorFiller(floor()).randomFill();
}
