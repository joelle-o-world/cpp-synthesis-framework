#include "./wavetables.h"

Wavetable sawtoothWavetable;
Wavetable sineWavetable;
Wavetable squareWavetable;
Wavetable triangleWavetable;

void initialiseWavetables() {
  float phase;
  for(int i = 0; i < WAVETABLE_SIZE; ++i) {
    phase = float(i) / float(WAVETABLE_SIZE);

    sawtoothWavetable[i] = phase * 2 - 1;

    sineWavetable[i] = sin(phase * PHI);

    squareWavetable[i] = phase > .5 ? 1 : -1;

    if(phase < .25) {
      triangleWavetable[i] = phase * 4;
    } else if(phase < .75)
      triangleWavetable[i] = 2 - 4 *phase;
    else 
      triangleWavetable[i] = 4*phase - 4;
  }
}
