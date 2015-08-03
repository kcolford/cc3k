#ifndef TEXTVIEW_HH
#define TEXTVIEW_HH

#include "View.hh"
#include "smart_ptr.hh"
#include <string>
#include <sstream>

class PlayerStats;

struct TextView: View {
  char display[width][height];
  PlayerStats *ourstats;
  std::stringstream command;
  std::string old_command;

  TextView();
  virtual void put(char ch);
  virtual std::string getline();
  virtual void poll_input();
  void put(std::string s);
  void update_scene(SceneGraph &s);
  void draw();
  std::string get_event();
  std::string get_user_input(std::string prompt);
  void update_hud(PlayerStats &stats);
  void big_notification(std::string message);

};

#endif
