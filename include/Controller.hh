#ifndef CONTROLLER_HH
#define CONTROLLER_HH

class GameObject;
class Character;

class Controller
{
public:
  virtual ~Controller() {}
  virtual void update(GameObject &o) = 0;
  virtual void get_attacked(const Character &attacker __attribute__((__unused__))) {}
};

#endif
