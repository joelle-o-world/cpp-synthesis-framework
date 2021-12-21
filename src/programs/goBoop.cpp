#include "goBoop.h"

void goBoop() {

  initialiseWavetables();

  play(decay(.2) * osc(440));
}
