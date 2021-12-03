#include "goBoop.h"
#include <iostream>

void goBoop() {
  std::cout << "goBoop program\n";

  initialiseWavetables();

  std::cout << "creating envelope\n";
  Decay envelope;
  envelope.inputs[0].connect(.2);

  std::cout << "creating source\n";
  Osc source;
  source.inputs[0].connect(440);
  source.waveform = &sineWavetable;

  std::cout << "creating gain\n";
  Multiply gain;
  std::cout << "1\n";
  gain.inputs[0].connect(source.outputs[0]);
  std::cout << "2\n";
  gain.inputs[1].connect(envelope.outputs[0]);

  envelope.retrigger();

  std::cout << "creating circuit\n";
  
  Circuit circuit = Circuit(&gain);



  std::cout << "playing...\n";
  play(circuit);

  std::cout << "I went boop!\n";
}
