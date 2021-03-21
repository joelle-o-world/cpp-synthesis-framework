#pragma once
#include "../AudioProcess.h"
#include "../AudioProcessCoordinator.h"
#include "../wavetables.h"



/**
 * Simple k/a-rate frequency wavetable oscillator.
 */
class _Osc : public AudioProcess {
  float phase = 0;

  public:
    float frequency = 440;
    Wavetable* waveform = &sineWavetable;

    _Osc() {
      inputs = new SignalBuffer*[1];
      outputs = new SignalBuffer*[1];
    }

    void process() override {
      SignalBuffer& out = *outputs[0];

      if(inputs[0] != NULL) {
        SignalBuffer& f = *inputs[0];
        // a-rate mode
        for(int i=0; i < signalChunkSize; ++i) {
          phase += f[i] * sampleInterval;
          while(phase > 1)
            --phase;
          while(phase < 0)
            ++phase;

          int j = phase * WAVETABLE_SIZE;
          out[i] = (*waveform)[j];
        }
      } else {
        // k-rate mode
        for(int i=0; i < signalChunkSize; ++i) {
          phase += frequency * sampleInterval;
          while(phase > 1)
            --phase;
          while(phase < 0)
            ++phase;
          int j = phase * WAVETABLE_SIZE;
          out[i] = (*waveform)[j];
        }
      }
    }
};

