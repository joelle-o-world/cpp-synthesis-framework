#include "./FTM.h"
#include "../connect.h"

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
