#include "TypedSignalBuffer.h"
#include <iostream>

void copyData(float *from, float *to) {
  std::cout << "copyData\n";
  for (int i = 0; i < sizeof(StereoBuffer); ++i)
    to[i] = from[i];
}
