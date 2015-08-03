#ifndef GOLD_HH
#define GOLD_HH

#include "GameObjectPtr.hh"

enum gold_type {
  PILE_SMALL = 1,
  PILE_NORMAL = 2,
  PILE_MERCHANT = 4,
  PILE_DRAGON = 6,
};

GameObjectPtr make_gold(gold_type amount);

#endif
