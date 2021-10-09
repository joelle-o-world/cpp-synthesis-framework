#pragma once

#include <math.h>

#include "../AudioProcess.h"

class FTM : public AudioProcess {
  public:
    FTM():AudioProcess(1,1) { }

    void process() override {
      SignalBuffer& in = *inputs[0];
      SignalBuffer& out = *outputs[0];

      for(int i=0; i < signalChunkSize; ++i)
        out[i] = 440.0 * pow(2.0, (in[i] - 69.0) / 12.0);
    }
};

class SemitoneToRatio : public AudioProcess {
  public:
    SemitoneToRatio(): AudioProcess(1,1) {
      inputs = new SignalBuffer*[1];
      outputs = new SignalBuffer*[1];
    }

    void process() override {
      SignalBuffer& in = *inputs[0];
      SignalBuffer& out = *outputs[0];

      for(int i=0; i < signalChunkSize; ++i)
        out[i] = pow(2.0, in[i] / 12.0);
    }
};
