#ifndef FLOORFILLER_HH
#define FLOORFILLER_HH

#include "Floor.hh"
#include <utility>
#include <vector>

struct FloorFiller
{
  static const int max_chambers = 5;

  FloorPtr floor;
  std::vector<std::pair<int, int> > chambers[max_chambers];
  int chamber_count;
  std::vector<std::pair<int, int> > *cells[Floor::width][Floor::height];

  FloorFiller(FloorPtr f);
  bool is_open(int x, int y);
  void run(int x, int y, std::vector<std::pair<int, int> > *chamber = NULL);
  void randomFill();

};

#endif
