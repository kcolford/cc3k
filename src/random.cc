#include "random.hh"
#include <cassert>
#include <cstdlib>
#include <ctime>

static const int max_iterations = 8;

double r()
{
  double r;
  for (int i = 0; i < max_iterations; i++) {
    r = rand();
    if (r != RAND_MAX)
      break;
  }

  if (r == RAND_MAX)
    r = 0;
  
  double out = (double) r / (double) RAND_MAX;
  assert(out < 1.0);
  return out;
}
