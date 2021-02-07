#include <math.h>
#include "Osc.h"

const float PI = 3.14159265;
const float PHI = 2.0 * PI;

void Osc::process() {
  const float dPhasePerSample = PHI * frequency / SAMPLE_RATE;
  float* out = outlets[0]->buffer;
  for(int i=0; i < CHUNK_SIZE; i++) {
    phase = fmod(phase + dPhasePerSample, PHI);
    *(out++) = sin(phase);
  }
}
