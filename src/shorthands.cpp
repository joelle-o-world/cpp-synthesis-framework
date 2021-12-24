#include "shorthands.h"

void connect(float k, Inlet &inlet) {
  auto c = new Constant(k);
  connect(*c, inlet);
}

Decay &decay(float halfLife) {
  Decay *p = new Decay;
  connect(halfLife, p->inputs[0]);
  return *p;
}
Decay &decay(AudioProcess &halfLife) {
  Decay *p = new Decay;
  connect(halfLife, p->inputs[0]);
  return *p;
}

// TODO: Probably want to use smart pointers
Multiply &multiply(AudioProcess &a, AudioProcess &b) {
  Multiply *p = new Multiply;
  connect(a, p->inputs[0]);
  connect(b, p->inputs[1]);
  return *p;
}

Multiply &operator*(AudioProcess &a, AudioProcess &b) { return multiply(a, b); }

Add &add(AudioProcess &a, AudioProcess &b) {
  Add *p = new Add();
  connect(a, p->inputs[0]);
  connect(b, p->inputs[1]);
  return *p;
}

Add &operator+(AudioProcess &a, AudioProcess &b) { return add(a, b); }

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

float st(float semitones) { return pow(2.0, (semitones - 69.0) / 12.0); }

SemitoneToRatio &st(AudioProcess &semitones) {
  SemitoneToRatio *p = new SemitoneToRatio;
  connect(semitones, p->inputs[0]);
  return *p;
}

float pitch(float note) { return 440.0 * pow(2.0, (note - 69.0) / 12.0); }
MTF &pitch(AudioProcess &note) {
  MTF *p = new MTF;
  connect(note, p->inputs[0]);
  return *p;
}
