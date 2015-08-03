#ifndef ENEMY_HH
#define ENEMY_HH

#include "GameObjectPtr.hh"
#include <string>

GameObjectPtr make_enemy(char type);
GameObjectPtr make_dragon(GameObjectPtr guarding);

#endif
