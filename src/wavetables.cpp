#include "./wavetables.h"

void initialiseWavetables() {
  for(int i = 0; i < WAVETABLE_SIZE; ++i) {
    float phase = 1.0 / float(WAVETABLE_SIZE);
    sawtoothWaveTable[i] = phase * 2 - 1;
  }
}
