#include <iostream> 

#include "./processes/Osc.h"
#include "./processes/Add.h"
#include "./processes/Multiply.h"
#include "./processes/FTM.h"
#include "./wavetables.h"

using std::cout;
int main() {
  initialiseWavetables();

  SignalBuffer b1, b2,b3;

  _Osc carrier, modulator;

  _Multiply modulationIntensity;

  _Add sum;

  modulator.outputs[0] = &b1;
  modulationIntensity.a = 100;
  modulationIntensity.inputs[1] = &b1;
  modulationIntensity.outputs[0] = &b1;

  sum.a = 69;
  sum.inputs[1] = &b1;
  sum.outputs[0] = &b1;

  _FTM ftm;
  ftm.inputs[0] = &b1;
  ftm.outputs[0] = &b1;

  carrier.inputs[0] = &b1;
  carrier.outputs[0] = &b1;

  modulator.frequency = 20;


  for(int i=0; true; ++i) {
    modulator.process();
    modulationIntensity.process();
    sum.process();
    ftm.process();
    carrier.process();
    modulationIntensity.a = modulationIntensity.a * .99;

    modulator.frequency += .1;
    fwrite(b1, sizeof(float), signalChunkSize, stdout);
  }
}
