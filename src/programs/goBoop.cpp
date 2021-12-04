#include "goBoop.h"
#include <iostream>

void goBoop() {

  initialiseWavetables();

  Decay envelope;
  envelope.inputs[0].connect(.2);

  Osc source;
  source.inputs[0].connect(440);
  source.waveform = &sineWavetable;

  Multiply gain;
  gain.inputs[0].connect(source.outputs[0]);
  gain.inputs[1].connect(envelope.outputs[0]);

  envelope.retrigger();

  
  Circuit circuit = Circuit(&gain);


  circuit.prepare();
  circuit.dotGraph(std::cout);

  //play(circuit);

}
