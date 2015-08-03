#ifndef SCENEGRAPHPTR_HH
#define SCENEGRAPHPTR_HH

#include "smart_ptr.hh"

struct SceneGraph;
typedef shared_ptr<SceneGraph> SceneGraphPtr;

SceneGraphPtr make_scene_graph(char m, int x, int y);

inline
SceneGraphPtr make_scene_graph(char m)
{
  return make_scene_graph(m, 0, 0);
}

#endif
