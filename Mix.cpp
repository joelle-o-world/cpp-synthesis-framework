#include "Mix.h"

void Mix::process() {
  float* a = inlets[0] -> buffer;
  float* b = inlets[1] -> buffer;
  float* out = outlets[0] -> buffer;
  for(int i=0; i < CHUNK_SIZE; ++i)
    *(out++) = (*(a++) + *(b++)) / 2;
}
