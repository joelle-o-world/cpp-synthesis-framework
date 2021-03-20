#pragma once
#include "../AudioProcess.h"
#include "../AudioProcessCoordinator.h"

#include <iostream>

class _Osc : public AudioProcess {
  float phase = 0;

  public:
    _Osc() {
      inputs = new SignalBuffer*[0];
      outputs = new SignalBuffer*[1];
    }

    float frequency = 440;
    void process() override {
      SignalBuffer* out = outputs[0];
      for(int i=0; i < signalChunkSize; ++i) {
        phase += frequency * sampleInterval;
        while(phase > 1)
          --phase;
        while(phase < 0)
          ++phase;
        (*out)[i] = phase * 2.0 - 1.0;
      }
    }
};

