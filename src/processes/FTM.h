#pragma once

#include <math.h>

#include "../AudioProcess.h"

class _FTM : public AudioProcess {
  public:
    _FTM():AudioProcess(1,1) {
      inputs = new SignalBuffer*[1];
      outputs = new SignalBuffer*[1];
    }

    void process() override {
      SignalBuffer& in = *inputs[0];
      SignalBuffer& out = *outputs[0];

      for(int i=0; i < signalChunkSize; ++i)
        out[i] = 440.0 * pow(2.0, (in[i] - 69.0) / 12.0);
    }
};

class _SemitoneToRatio : public AudioProcess {
  public:
    _SemitoneToRatio(): AudioProcess(1,1) {
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
