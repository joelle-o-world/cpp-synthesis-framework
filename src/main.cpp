#include <iostream> 

#include "./processes/Osc.h"
#include "./processes/Add.h"
#include "./processes/Multiply.h"

int main() {

  SignalBuffer b1, b2,b3;

  _Osc osc1, osc2;
  osc1.frequency = 440;
  osc2.frequency = 110;

  osc1.out = &b1;
  osc2.out = &b2;


  _Add adder;
  adder.a = &b1;
  adder.b = &b2;
  adder.out = &b3;

  _Multiply multiply;
  multiply.scaleFactor = .25;
  multiply.a = &b3;
  multiply.out = &b3;

  for(int i=0; true; ++i) {
    osc1.process();
    osc2.process();
    adder.process();
    multiply.process();
    fwrite(b3, sizeof(float), signalChunkSize, stdout);
  }
}
