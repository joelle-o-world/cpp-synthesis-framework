#pragma once

#include "../AudioProcess.h"
#include "./Osc.h"
#include "./FTM.h"
#include "./Multiply.h"

class FMOsc : public AudioProcess {
  private:
    SemitoneToRatio semitonToRatio;
    Multiply mult;
    Osc carrier;
    SignalBuffer internalBuffer;

  public:
    FMOsc(): AudioProcess(2,1) { }

    void process() {
      semitonToRatio.process(*inputs[1], internalBuffer);
      mult.process(*inputs[0], internalBuffer, internalBuffer);
      carrier.process(internalBuffer, *outputs[0]);
    }
};
