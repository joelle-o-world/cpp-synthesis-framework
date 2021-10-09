#include <iostream>

#include "./processes/Add.h"
#include "./processes/FTM.h"
#include "./processes/Multiply.h"
#include "./processes/Osc.h"
#include "./wavetables.h"

using std::cout;
int main() {
  initialiseWavetables();

  StereoBuffer sb1, sb2, sb3, sb4;
  float sixtynine = 69.0;
  TypedSignalBuffer b1 = {Stereo, &sb1};
  TypedSignalBuffer b2 = {.type = Constant, .constant = &sixtynine};

  Osc carrier, modulator;

  Multiply modulationIntensity;

  Add sum;

  modulator.outputs[0] = &b1;
  modulationIntensity.a = 100;
  modulationIntensity.inputs[1] = &b1;
  modulationIntensity.outputs[0] = &b1;

  sum.inputs[0] = &b2;
  sum.inputs[1] = &b1;
  sum.outputs[0] = &b1;

  FTM ftm;
  ftm.inputs[0] = &b1;
  ftm.outputs[0] = &b1;

  carrier.inputs[0] = &b1;
  carrier.outputs[0] = &b1;

  modulator.inputs[0]->constant = new float(20);

  for (int i = 0; true; ++i) {
    modulator.process();
    modulationIntensity.process();
    sum.process();
    ftm.process();
    carrier.process();
    modulationIntensity.a = modulationIntensity.a * .99;

    modulator.frequency += .1;
    fwrite(b1.stereo, sizeof(float), signalChunkSize, stdout);
  }
}
