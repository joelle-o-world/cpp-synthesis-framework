#include <iostream> 

#include "./processes/Osc.h"
#include "./processes/Add.h"
#include "./processes/Multiply.h"
#include "./wavetables.h"

using std::cout;
int main() {
  initialiseWavetables();

  SignalBuffer b1, b2,b3;

  _Osc carrier, modulator;

  _Multiply modulationIntensity;

  _Add sum;

  modulator.outputs[0] = &b1;
  modulationIntensity.a = 1000;
  modulationIntensity.inputs[1] = &b1;
  modulationIntensity.outputs[0] = &b1;

  sum.a = 200;
  sum.inputs[1] = &b1;
  sum.outputs[0] = &b1;

  carrier.inputs[0] = &b1;
  carrier.outputs[0] = &b1;

  modulator.frequency = 300;


  for(int i=0; true; ++i) {
    modulator.process();
    modulationIntensity.process();
    sum.process();
    carrier.process();
    modulationIntensity.a += 1;

    modulator.frequency -= .1;
    fwrite(b1, sizeof(float), signalChunkSize, stdout);
  }
}
