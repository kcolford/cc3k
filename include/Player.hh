#ifndef PLAYER_HH
#define PLAYER_HH

#include "GameObjectPtr.hh"
#include <string>

GameObjectPtr make_player(std::string cls);
GameObjectPtr player();         // game.player()
void player_used_potion(std::string name);

#endif
