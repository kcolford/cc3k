#include "SceneGraph.hh"
#include <boost/foreach.hpp>

SceneGraph::SceneGraph()
  : visible(true)
  , parent()
{}

static bool operator==(const boost::weak_ptr<SceneGraph> &l,
                       const boost::weak_ptr<SceneGraph> &r)
{
  SceneGraphPtr lp = l.lock(), rp = r.lock();
  if (lp && rp)
    return lp == rp;
  else if (!lp && !rp)
    return true;
  else
    return false;
}

void SceneGraph::sub(SceneGraphPtr p)
{
  if (SceneGraphPtr par = parent.lock())
    par->subgraph.remove(p);

  subgraph.push_back(p);
  p->parent = shared_from_this();
}

SceneGraph::~SceneGraph()
{
  ;
}

SceneGraphPtr make_scene_graph(char m, int x, int y)
{
  SceneGraphPtr out = make_shared<SceneGraph>();
  out->mesh = m;
  out->x = x;
  out->y = y;
  return out;
}

void SceneGraph::update(int newx, int newy)
{
  x = newx;
  y = newy;
}
