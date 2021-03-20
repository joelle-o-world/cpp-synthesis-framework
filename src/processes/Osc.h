#pragma once
#include "../AudioProcess.h"
#include "../AudioProcessCoordinator.h"

class _Osc : public AudioProcess {
  float * wavetable;
  float phase = 0;

  public:
    float frequency = 440;
    void process() override {
      for(int i=0; i < signalChunkSize; ++i) {
        phase += frequency * sampleInterval;
        outletbuffers[0][i] = phase * 2.0 - 1.0;
      }
    }
};

