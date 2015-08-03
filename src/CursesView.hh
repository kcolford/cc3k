#ifndef CURSESVIEW_HH
#define CURSESVIEW_HH

#include "TextView.hh"
#include "shared_ptr.hh"
#include <string>

struct CursesView: TextView {
  void put(char c);
  std::string getline();
  CursesView();
  ~CursesView();
  void poll_input();
  void draw();
};

#endif
