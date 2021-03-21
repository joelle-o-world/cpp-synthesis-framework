#include <iostream> 

#include "./processes/Osc.h"
#include "./processes/Add.h"
#include "./processes/Multiply.h"
#include "./wavetables.h"

using std::cout;
int main() {
  initialiseWavetables();

  SignalBuffer b1, b2,b3;

  _Osc osc1, osc2;
  osc1.frequency = .5;
  osc2.frequency = 880;

  osc1.outputs[0] = &b1;
  osc2.outputs[0] = &b2;


  _Multiply multiply;
  multiply.inputs[0] = &b1;
  multiply.inputs[1] = &b2;
  multiply.outputs[0] = &b3;

  for(int i=0; true; ++i) {
    osc1.process();
    osc2.process();
    osc2.frequency -= .1;
    multiply.process();
    fwrite(b3, sizeof(float), signalChunkSize, stdout);
  }
}
