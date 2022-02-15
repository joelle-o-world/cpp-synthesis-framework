#include "./Osc.h"

Osc &osc(float frequency) {
  Osc *p = new Osc();
  p->waveform = &sineWavetable;
  connect(frequency, p->inputs[0]);
  return *p;
}
Osc &osc(AudioProcess &frequency) {
  Osc *p = new Osc();
  p->waveform = &sineWavetable;
  connect(frequency, p->inputs[0]);
  return *p;
}
