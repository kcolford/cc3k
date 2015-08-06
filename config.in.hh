#ifndef CONFIG_HH
#define CONFIG_HH

// Whether or not we have found the curses library on this system.
#cmakedefine01 CURSES_FOUND

// Do we have <curses.h>
#cmakedefine01 CURSES_HAVE_CURSES_H

// Do we have <ncurses.h>
#cmakedefine01 CURSES_HAVE_NCURSES_H

// Do we have <curses/curses.h>
#cmakedefine01 CURSES_HAVE_CURSES_CURSES_H

// Do we have <ncurses/ncurses.h>
#cmakedefine01 CURSES_HAVE_NCURSES_NCURSES_H

// Should the advanced mode be enabled by default?
#cmakedefine ENABLE_DEFAULT_ADVANCED_GAME

#endif
