#include <config.h>
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
  if (false)
    return make_shared<TextView>();
#if CURSES_FOUND
  else if (config["use_curses"])
    return make_shared<CursesView>();
#endif
  else if (true)
    return make_shared<TextView>();

}
