#include "CursesView.hh"
#include <ncurses.h>
#include <climits>
#include <cstring>
#include <string>
#include <clocale>

void CursesView::put(char c)
{
  addch(std::strchr("@", c) ? c | A_BOLD : c);
}

std::string CursesView::getline()
{
  int c;
  std::string s;
  echo();
  while ((c = getch()) != '\n') {
    s.push_back(c);
  }
  noecho();
  return s;
}

CursesView::CursesView()
{
  std::setlocale(LC_ALL, "");
  initscr(); cbreak(); noecho();
#if 0
  keypad(stdscr, TRUE);
#endif
}

CursesView::~CursesView()
{
  endwin();
}

void CursesView::poll_input()
{
  command.str("");
  command.clear();
  int ch = getch();
  echochar(ch);
  switch (ch) {
    //case KEY_SUP:
  case 'W':
    command << "a ";
  case KEY_UP:
  case 'w':
    command << "no";
    break;
  case KEY_SLEFT:
  case 'A':
    command << "a ";
  case KEY_LEFT:
  case 'a':
    command << "we";
    break;
    //case KEY_SDOWN:
  case 'S':
    command << "a ";
  case KEY_DOWN:
  case 's':
    command << "so";
    break;
  case KEY_SRIGHT:
  case 'D':
    command << "a ";
  case KEY_RIGHT:
  case 'd':
    command << "ea";
    break;
  case KEY_ENTER:
    break;
  default:
    command << ' ' << (char) ch << getline();
    break;
  }
}

void CursesView::draw() {
  move(0, 0);
  clear();
  TextView::draw();
  refresh();
}

