#ifndef SCENEGRAPH_HH
#define SCENEGRAPH_HH

#include "shared_ptr.hh"
#include <list>
#include <vector>

struct SceneGraph;
typedef shared_ptr<SceneGraph> SceneGraphPtr;

struct SceneGraph 
  : enable_shared_from_this<SceneGraph>
{
private:
  SceneGraph();
  friend SceneGraphPtr make_shared<SceneGraph>();

private:
  char mesh;
  int x;
  int y;
  unsigned visible : 1;
  friend class GameObject;
  boost::weak_ptr<SceneGraph> parent;
  friend SceneGraphPtr make_scene_graph(char m, int x, int y);
  friend class View;

  std::list<boost::weak_ptr<SceneGraph> > subgraph;

public:
  void sub(SceneGraphPtr p);

public:
  void update(int newx, int newy);

  ~SceneGraph();

private:
  SceneGraph(const SceneGraph &other);
  SceneGraph &operator=(SceneGraph other);

};

SceneGraphPtr make_scene_graph(char m, int x, int y);

inline
SceneGraphPtr make_scene_graph(char m)
{
  return make_scene_graph(m, 0, 0);
}

#endif
