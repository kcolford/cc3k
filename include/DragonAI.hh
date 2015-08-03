#ifndef DRAGONAI_HH
#define DRAGONAI_HH

#include "Controller.hh"
#include "GameObject.hh"

struct DragonAI: Controller {
  GameObjectPtr guarding;

  DragonAI(GameObjectPtr g);  
  ~DragonAI();
  void update(GameObject &me);

private:
  DragonAI(const DragonAI &other);
  DragonAI &operator=(DragonAI other);

};


#endif
