#ifndef COLLISION_MASKS_HH
#define COLLISION_MASKS_HH

enum collision_masks {
  COLL_PLAYER     = 0x1,
  COLL_OPEN_FLOOR = 0x2,
  COLL_WALL       = 0x4,
  COLL_DOOR       = 0x8,
  COLL_STAIRS     = 0x10,
  COLL_PASSAGE    = 0x20,

  COLL_EVERYTHING = ~0,
  COLL_NOTHING    = 0,
};

#endif
