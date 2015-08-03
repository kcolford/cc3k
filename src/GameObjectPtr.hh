#ifndef GAMEOBJECTPTR_HH
#define GAMEOBJECTPTR_HH

#include "shared_ptr.hh"

class GameObject;
typedef boost::shared_ptr<GameObject> GameObjectPtr;

GameObjectPtr make_basic_object(char type);
GameObjectPtr make_object(char type);

#endif
