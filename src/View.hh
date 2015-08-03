#ifndef VIEW_HH
#define VIEW_HH

#include "shared_ptr.hh"
#include <string>
#include <iostream>
#include <set>

class Game;
class PlayerStats;
class SceneGraph;
typedef shared_ptr<SceneGraph> SceneGraphPtr;

class View
{
private:
  virtual void update_scene(SceneGraph &s) = 0;
  virtual void draw() = 0;
  virtual void update_hud(PlayerStats &stats) = 0;
  
  int x_offset_;
  int y_offset_;

#if DEBUG
  std::set<SceneGraphPtr> cache;
#endif

protected:
  void recurse_scene(SceneGraphPtr s);
  char getMesh(const SceneGraph &s) const;
  int getX(const SceneGraph &s) const;
  int getY(const SceneGraph &s) const;
  bool isVisible(const SceneGraph &s) const;

public:
  View();
  virtual ~View() {}
  void update(Game &game);

  virtual void poll_input() = 0;
  virtual std::string get_event() = 0;

  virtual std::string get_user_input(std::string prompt = "") = 0;
  virtual void big_notification(std::string message) = 0;
  void big_notification(std::istream &message);

  static const int width = 79;
  static const int height = 25;

};

#endif
