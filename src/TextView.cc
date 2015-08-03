#include "TextView.hh"
#include "PlayerStats.hh"
#include "Floor.hh"
#include <iostream>
#include <cctype>
#include <cstring>
#include <sstream>
#include <locale>
#include <iomanip>
#include <boost/foreach.hpp>

using std::swap;

std::ostream &clear(std::ostream &stream)
{
  stream.clear();
  return stream;
}

struct EOFError {};

void TextView::put(char ch)
{
  std::cout << ch;
}

std::string TextView::getline()
{
  std::string s;
  if (!std::getline(std::cin, s))
    throw EOFError();
  return s;
}

void TextView::put(std::string s)
{ BOOST_FOREACH(char c, s) put(c); }

TextView::TextView() {
  std::memset(display, 0, sizeof display);
}

void TextView::update_scene(SceneGraph &s) {
  assert((unsigned) getX(s) < width);
  assert((unsigned) getY(s) < height);
  display[getX(s)][getY(s)] = getMesh(s);
}


void TextView::draw() {
  for (int y = height - 1; y >= 0; y--) {
    for (int x = 0; x < width; x++)
      put(std::isprint(display[x][y]) ? display[x][y] : ' ');
    put('\n');
  }

  PlayerStats &stats = *ourstats;
  stats.race[0] = std::toupper(stats.race[0]);
    
  std::stringstream racemessage;
  racemessage << "Race: " << stats.race << " Gold: " << stats.gold();

  std::stringstream floormessage;
  floormessage << "Floor: " << stats.floor();

  std::stringstream out;
  out << std::left << std::setw(width - floormessage.str().size())
      << racemessage.str()
      << floormessage.str()
      << std::endl
    ;

  out << std::left
      << "HP: " << stats.health() << std::endl
      << "Atk: " << stats.atk() << std::endl
      << "Def: " << stats.def() << std::endl
      << "Action: " << stats.action.rdbuf() << clear << std::endl
    ;

  put(out.str());    
}

void TextView::poll_input()
{
  std::string c = getline();
  if (!c.empty())
    old_command = c;
  command.clear();
  command.str(old_command);
}

std::string TextView::get_event() {
  std::string s;
  command >> std::ws >> s;
  return s;
}

std::string TextView::get_user_input(std::string prompt) {
  put(prompt + " ");
  std::string input = getline();
  return input;
}

void TextView::update_hud(PlayerStats &stats) {
  ourstats = &stats;
}

void TextView::big_notification(std::string message) {
  put("\n" + message + "\n");
}

    
