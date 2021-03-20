#pragma once
#include "../AudioProcess.h"
#include "../AudioProcessCoordinator.h"

#include <iostream>

class _Osc : public AudioProcess {
  float * wavetable;
  float phase = 0;

  public:
    SignalBuffer* out;
    //_Osc() {
      //inletbuffers = new SignalBuffer*[0];
      //outletbuffers = new SignalBuffer*[1];
    //}
    float frequency = 440;
    void process() override {
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

