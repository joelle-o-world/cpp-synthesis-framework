#include "./Osc.h"

Osc &osc(float frequency) {
  Osc *p = new Osc();
  p->waveform = &sineWavetable;
  connect(frequency, p->inputs[0]);
  return *p;
}
Osc &osc(Component &frequency) {
  Osc *p = new Osc();
  p->waveform = &sineWavetable;
  connect(frequency, p->inputs[0]);
  return *p;
}
