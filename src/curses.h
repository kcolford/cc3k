#ifndef CC3K_CURSES_H
#define CC3K_CURSES_H

#include <config.hh>

#if CURSES_FOUND
# if CURSES_HAVE_CURSES_H
#  include <curses.h>
# elif CURSES_HAVE_NCURSES_H
#  include <ncurses.h>
# elif CURSES_HAVE_CURSES_CURSES_H
#  include <curses/curses.h>
# elif CURSES_HAVE_NCURSES_NCURSES_H
#  include <ncurses/ncurses.h>
# else
#  error "Curses was found but no valid header was identified for it."
# endif
#endif

#endif
