#include "View.hh"
#include "SceneGraph.hh"
#include "Game.hh"
#include <cassert>
#include <boost/foreach.hpp>

View::View()
  : x_offset_(0)
  , y_offset_(0)
{}

void View::recurse_scene(SceneGraphPtr s)
{
  assert(s);

  if (!s->visible) return;

  if (s->mesh)
    update_scene(*s);
    
  x_offset_ += s->x;
  y_offset_ += s->y;
  BOOST_FOREACH(boost::weak_ptr<SceneGraph> pp, s->subgraph)
    if (SceneGraphPtr p = pp.lock())
      recurse_scene(p);
  x_offset_ -= s->x;
  y_offset_ -= s->y;
}

char View::getMesh(const SceneGraph &s) const
{
  return s.mesh;
}

int View::getX(const SceneGraph &s) const
{
  return x_offset_ + s.x;
}

int View::getY(const SceneGraph &s) const
{
  return y_offset_ + s.y;
}

bool View::isVisible(const SceneGraph &s) const
{
  return s.visible;
}

void View::update(Game &game)
{
  assert(this);

#if DEBUG
  cache.clear();
#endif

  recurse_scene(game.scene);
  update_hud(game.stats);
  draw();
}

void View::big_notification(std::istream &message)
{
  message >> std::noskipws;
  std::string s(std::istream_iterator<char>(message),
                (std::istream_iterator<char>()));
  big_notification(s);
}

