#ifndef COLLECTGOLD_HH
#define COLLECTGOLD_HH

#include "CollectComponent.hh"

struct CollectGold: CollectComponent {
  int mygold;
  CollectGold(int g);
  void collectMe(GameObject &me, Character &collector);
};


#endif
