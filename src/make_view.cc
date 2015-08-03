#include <config.hh>
#include "make_view.hh"
#include "main.hh"
#include "View.hh"

// The views.
#include "TextView.hh"
#if CURSES_FOUND
# include "CursesView.hh"
#endif

shared_ptr<View> make_view()
{
  if (false);

#if CURSES_FOUND
  else if (config["use_curses"]) return make_shared<CursesView>();
#endif
  
  return make_shared<TextView>();
}
