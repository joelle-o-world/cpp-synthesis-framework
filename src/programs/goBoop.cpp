#include "goBoop.h"
#include "../connect.h"
#include <iostream>

void goBoop() {

  initialiseWavetables();

  Decay envelope;
  connect(.2, envelope.inputs[0]);

  Osc source;
  connect(440, source.inputs[0]);
  source.waveform = &sineWavetable;

  Multiply gain;
  connect(envelope.outputs[0], gain.inputs[1]);
  connect(source.outputs[0], gain.inputs[0]);

  envelope.retrigger();

  Circuit circuit = Circuit(&gain);

  circuit.prepare();
  circuit.easyGraph(std::cout);

  play(circuit);
}
