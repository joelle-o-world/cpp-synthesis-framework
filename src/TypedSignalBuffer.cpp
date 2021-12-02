#include "TypedSignalBuffer.h"

void copyData(TypedSignalBuffer *from, StereoBuffer* to) {
  if (from->type == Stereo) {
    for(int i=0; i < sizeof(StereoBuffer); ++i)
      (*to)[i] = (*(from->stereo))[i];
  }
}
