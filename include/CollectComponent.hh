#ifndef COLLECTCOMPONENT_HH
#define COLLECTCOMPONENT_HH

class GameObject;
class Character;

class CollectComponent
{
public:
  virtual ~CollectComponent() {}
  virtual void collectMe(GameObject &me, Character &collector) = 0;
};

#endif
