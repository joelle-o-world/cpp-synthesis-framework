#include <iostream> 

#include "./processes/Osc.h"
#include "./processes/Add.h"
#include "./processes/Multiply.h"

int main() {

  SignalBuffer b1, b2,b3;

  _Osc osc1, osc2;
  osc1.frequency = 440;
  osc2.frequency = 10;

  osc1.outputs[0] = &b1;
  osc2.outputs[0] = &b2;


  _Add adder;
  adder.inputs[0] = &b1;
  adder.inputs[1] = &b2;
  adder.outputs[0] = &b3;

  _Multiply multiply;
  multiply.scaleFactor = .25;
  multiply.inputs[0] = &b3;
  multiply.outputs[0] = &b3;

  for(int i=0; true; ++i) {
    osc1.process();
    osc2.process();
    adder.process();
    multiply.process();
    fwrite(b3, sizeof(float), signalChunkSize, stdout);
  }
}
