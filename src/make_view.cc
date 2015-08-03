#include "make_view.hh"
#include "main.hh"
#include "View.hh"

// The views.
#include "TextView.hh"
#include "CursesView.hh"

shared_ptr<View> make_view()
{
  if (config["use_curses"])
    return make_shared<CursesView>();
  else
    return make_shared<TextView>();
}
