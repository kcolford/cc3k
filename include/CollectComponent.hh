#ifndef COLLECTCOMPONENT_HH
#define COLLECTCOMPONENT_HH

class GameObject;

class CollectComponent
{
public:
  virtual ~CollectComponent() {}
  virtual void collectMe(GameObject &me, GameObject &collector) = 0;
};

#endif
