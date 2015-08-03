#include "Game.hh"
#include "Floor.hh"
#include "Player.hh"
#include "collision_masks.hh"
#include "GameObject.hh"
#include <utility>
#include <cassert>
#include <cstring>

using namespace std;

static const int max_chambers = 5;

struct FloorFiller
{
  FloorPtr floor;
  vector<pair<int, int> > chambers[max_chambers];
  int chamber_count;
  vector<pair<int, int> > *cells[Floor::width][Floor::height];

  FloorFiller(FloorPtr f);
  bool is_open(int x, int y);
  void run(int x, int y, std::vector<std::pair<int, int> > *chamber = NULL);
  void randomFill();

};

FloorFiller::FloorFiller(FloorPtr f)
  : floor(f)
  , chamber_count(0)
{
  std::memset(cells, 0, sizeof cells);
  for (int i = 0; i < Floor::width; i++)
    for (int j = 0; j < Floor::height; j++)
      run(i, j);
}

bool FloorFiller::is_open(int x, int y)
{
  return floor->collision_mask(x, y) == COLL_OPEN_FLOOR;
}

void FloorFiller::run(int x, int y, 
                      std::vector<std::pair<int, int> > *chamber)
{
  if ((unsigned) x < Floor::width &&
      (unsigned) y < Floor::height &&
      cells[x][y] == NULL &&
      is_open(x, y)) {

    if (chamber == NULL) {
      assert(chamber_count < max_chambers);
      chamber = &chambers[chamber_count++];
    }
    assert(chamber_count <= max_chambers);

    cells[x][y] = chamber;
    cells[x][y]->push_back(std::make_pair(x, y));

    for (int xp = -1; xp < 2; xp++)
      for (int yp = -1; yp < 2; yp++)
        if (xp || yp)
          run(x + xp, y + yp, chamber);

  }
}

static const int max_iteration = 8;

void FloorFiller::randomFill()
{
  // Generate the player.
  int player_ch, player_coords;
  for (int i = 0; i < max_iteration; i++) {
    player_ch = chamber_count * r();
    assert((unsigned) player_ch < chamber_count);
    assert((unsigned) player_ch < max_chambers);
    player_coords = chambers[player_ch].size() * r();
    assert((unsigned) player_coords < chambers[player_ch].size());
    if (!game.player()->setPos(chambers[player_ch][player_coords]))
      break;
  }
  
  // Generate the stairs.
  for (int i = 0; i < max_iteration; i++) {
    int stair_ch, stair_coords;
    for (int j = 0; j < max_iteration; j++) {
      stair_ch = chamber_count * r();
      if (stair_ch != player_ch)
        break;
    }
    stair_coords = chambers[stair_ch].size() * r();
    if (!make_object('\\')->setPos(chambers[stair_ch][stair_coords]))
      break;
  }

  // Generate 10 potions.
  for (int i = 0; i < 10; i++) {
    GameObjectPtr p = make_object('0' + 6 * r());
    int po_ch = chamber_count * r();
    for (int j = 0; j < max_iteration; j++) {
      int po_coords = chambers[po_ch].size() * r();
      if (!p->setPos(chambers[po_ch][po_coords]))
        break;
    }
  }
  
  // Generate 10 gold piles.
  for (int i = 0; i < 10; i++) {
    GameObjectPtr p = make_object('6' + 4 * r());
    int go_ch = chamber_count * r();
    for (int j = 0; j < max_iteration; j++) {
      int go_coords = chambers[go_ch].size() * r();
      if (!p->setPos(chambers[go_ch][go_coords]))
        break;
    }
  }

  // Generate 20 enemies.
  for (int i = 0; i < 20; i++) {
    // This string represents the distribution for enemies being
    // spawned.
    static const char enemy_types[] = "hhhhwwwllllleeoomm";
    GameObjectPtr p = make_object(enemy_types
                                  [(int) ((sizeof enemy_types) * r())]);
    int go_ch = chamber_count * r();
    for (int j = 0; j < max_iteration; j++) {
      int go_coords = chambers[go_ch].size() * r();
      if (!p->setPos(chambers[go_ch][go_coords]))
        break;
    }
  }
  
}

void Game::fillFloor()
{
  if (!floor()->is_filled)
    FloorFiller(floor()).randomFill();
}
