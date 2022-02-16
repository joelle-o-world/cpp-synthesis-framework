#include "goBoop.h"

void goBoop() {

  initialiseWavetables();

  play(decay(.05) * osc(pitch(decay(.3) * 80.0) - .5), .5);
}
