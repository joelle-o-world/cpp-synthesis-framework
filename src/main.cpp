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
  TypedSignalBuffer c1 = {.type = Constant, .constant = &sixtynine};

  Osc osc;
  osc.inputs[0] = &c1;
  osc.outputs[0] = &b1;

  Multiply mult;
  mult.inputs[0] = &b1;
  mult.inputs[1] = &b1;
  mult.outputs[0] = &b1;


  for (int i = 0; true; ++i) {
    
    osc.process();
    mult.process();

    fwrite(b1.stereo, sizeof(float), signalChunkSize*2, stdout);
  }
}
