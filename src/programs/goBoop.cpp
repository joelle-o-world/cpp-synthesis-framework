#include "goBoop.h"
#include <iostream>

void goBoop() {
  std::cout << "goBoop program\n";

  initialiseWavetables();

  Multiply gain;
  Decay envelope;
  Osc source;
  source.inputs[0].connect(440);
  source.waveform = &sineWavetable;
  Circuit circuit = Circuit(&source);

  circuit.prepare();
  play(circuit);

  std::cout << "I went boop!\n";
}
