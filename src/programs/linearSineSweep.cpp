#include "goBoop.h"
#include <iostream>

void goBoop() {

  initialiseWavetables();

  Decay envelope;
  envelope.inputs[0].connect(.2);

  Decay sweep;
  sweep.inputs[0].connect(1);
  sweep.retrigger();

  Multiply pitchEnvelope;
  pitchEnvelope.inputs[0].connect(300);
  pitchEnvelope.inputs[1].connect(sweep.outputs[0]);

  Osc source;
  source.inputs[0].connect(pitchEnvelope.outputs[0]);
  source.waveform = &sineWavetable;

  Multiply gain;
  gain.inputs[0].connect(source.outputs[0]);
  gain.inputs[1].connect(envelope.outputs[0]);

  envelope.retrigger();

  Circuit circuit = Circuit(&gain);

  circuit.prepare();
  circuit.easyGraph(std::cout);

  play(circuit);
}
