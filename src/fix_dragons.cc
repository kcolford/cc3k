#include "fix_dragons.hh"
#include "Game.hh"
#include "Gold.hh"
#include "Enemy.hh"
#include "GameObject.hh"
#include "DragonAI.hh"
#include "CollectGold.hh"
#include <boost/foreach.hpp>

void fix_dragons()
{
  for (int i = 0; i < Floor::width; i++)
    for (int j = 0; j < Floor::height; j++)
      BOOST_FOREACH(GameObjectPtr dragon, floor()->cells[i][j])
        if (dragon->controller)
          if (DragonAI *d =
              dynamic_cast<DragonAI *>(dragon->controller.get()))
            if (!d->guarding)
              for (int ioff = -1; ioff < 2; ioff++)
                for (int joff = -1; joff < 2; joff++)
                  if (ioff || joff) {
                    BOOST_FOREACH(GameObjectPtr gold,
                                  floor()->cells[i+ioff][j+joff])
                      if (gold->collect)
                        if (CollectGold *g =
                            dynamic_cast<CollectGold *>(gold->collect.get()))
                          if (g->mygold >= PILE_DRAGON)
                            d->guarding = gold;
                  }
}
