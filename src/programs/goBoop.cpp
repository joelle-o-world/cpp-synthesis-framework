#include "goBoop.h"

void goBoop() {

  initialiseWavetables();

  play(decay(.05) * osc(pitch(60)), .3);
  play(decay(.05) * osc(pitch(60)), .3);
  play(decay(.05) * osc(pitch(67)), .3);
  play(decay(.05) * osc(pitch(67)), .3);
  play(decay(.05) * osc(pitch(69)), .3);
  play(decay(.05) * osc(pitch(69)), .3);
  play(decay(.2) * osc(pitch(67)), .6);
}
