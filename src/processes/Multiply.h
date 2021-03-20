#pragma once

#include "../AudioProcess.h"

class _Multiply : public AudioProcess {
  public:
    SignalBuffer* a;
    SignalBuffer* out;
    float scaleFactor;

    void process() override {
      for(int i=0; i < signalChunkSize; ++i)
        (*out)[i] = (*a)[i] * scaleFactor;
    }
};
