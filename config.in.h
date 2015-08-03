#ifndef CONFIG_H
#define CONFIG_H

#cmakedefine01 CURSES_FOUND
#cmakedefine01 CURSES_HAVE_CURSES_H
#cmakedefine01 CURSES_HAVE_NCURSES_H

#if CURSES_FOUND
# if CURSES_HAVE_CURSES_H
#  define CURSES_HEADER "curses.h"
# elif CURSES_HAVE_NCURSES_H
#  define CURSES_HEADER "ncurses.h"
# else
#  undef CURSES_FOUND
#  define CURSES_FOUND 0
# endif
#endif

#endif
