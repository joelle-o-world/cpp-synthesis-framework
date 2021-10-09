#pragma once

#include "../AudioProcess.h"
#include "./Osc.h"
#include "./FTM.h"
#include "./Multiply.h"

class _FMOsc : public AudioProcess {
  private:
    _SemitoneToRatio str;
    _Multiply mult;
    _Osc carrier;
    SignalBuffer internalBuffer;

    _FMOsc(): AudioProcess(2,1) {
      inputs = new SignalBuffer*[2];
      outputs = new SignalBuffer*[1];
    }

    void process() {
      str.inputs[0] = inputs[1];
      str.outputs[0] = &internalBuffer;
      str.process();

      mult.inputs[0] = inputs[0];
      mult.inputs[1] = &internalBuffer;
      mult.outputs[0] = &internalBuffer;
      mult.process();

      carrier.inputs[0] = &internalBuffer;
      carrier.outputs[0] = outputs[0];
      carrier.process();

    }
};
