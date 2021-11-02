#include <iostream>

#include "./processes/arithmetic.h"
#include "./processes/FTM.h"
#include "./processes/Osc.h"
#include "./processes/Decay.h"
#include "./wavetables.h"
#include "./processes/GlitchyLoop.h"

using std::cout;
int main() {
  initialiseWavetables();

  StereoBuffer sb1, sb2, sb3, sb4;
  float sixtynine = 69.0;
  float hl = 1;
  TypedSignalBuffer b1 = {.type=Stereo, .stereo=&sb1};
  TypedSignalBuffer b2 = {.type=Stereo, .stereo=&sb2};
  TypedSignalBuffer c1 = {.type = Constant, .constant = &sixtynine};
  TypedSignalBuffer c2 = {.type=Constant, .constant = &hl};


  Decay decay2;

  GlitchyLoop gl;
  gl.inputs[0] = &c1;
  gl.outputs[0] = &b1;

  //Osc osc;
  //osc.inputs[0] = &c1;
  //osc.outputs[0] = &b1;

  Multiply mult;
  mult.inputs[0] = &b1;
  mult.inputs[1] = &b2;
  mult.outputs[0] = &b1;

  Decay decay1;
  decay1.inputs[0] = &c2;
  decay1.outputs[0] = &b2;


  decay1.retrigger();

  //osc.process(440, *b2.stereo);

  for (int i = 0; true; ++i) {
    
    //osc.process();
    gl.processStatefully();
    decay1.processStatefully();
    //cout << *b2.stereo;
    
    mult.processStatefully();

    fwrite(*b1.stereo, sizeof(float), signalChunkSize*2, stdout);
  }
}
