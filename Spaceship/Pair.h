
#ifndef  PAIR_H
#define PAIR_H

#include <Arduboy2.h>

struct Pair{
  int8_t first;
  int8_t second;
  Pair() : first(0), second(0){};
  Pair(int8_t x, int8_t y): first(x), second(y){};
};

#endif
