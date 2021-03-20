#pragma once

#include "../AudioProcess.h"

class _Multiply : public AudioProcess {
  public:
    //SignalBuffer* a;
    //SignalBuffer* out;
    float scaleFactor;

    _Multiply() {
      inputs = new SignalBuffer*[1];
      outputs = new SignalBuffer*[1];
    }

    void process() override {
      SignalBuffer* out = outputs[0];
      SignalBuffer* a = inputs[0];
      for(int i=0; i < signalChunkSize; ++i)
        (*out)[i] = (*a)[i] * scaleFactor;
    }
};
