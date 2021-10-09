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
  Wavetable *waveform = &sineWavetable;

  _Osc() : AudioProcess(1, 1) {}

  void process() override {
    SignalBuffer &out = *outputs[0];

    if (inputs[0] != nullptr) 
      process(*inputs[0], *outputs[0]);
    else
      // k-rate mode
      process(frequency, *outputs[0]);
  }

  // a-rate mode
  void process(SignalBuffer &frequency, SignalBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i) {
      phase += frequency[i] * sampleInterval;
      while (phase > 1)
        --phase;
      while (phase < 0)
        ++phase;

      int j = phase * WAVETABLE_SIZE;
      out[i] = (*waveform)[j];
    }
  }

  // k-rate mode
  void process(float frequency, SignalBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i) {
      phase += frequency * sampleInterval;
      while (phase > 1)
        --phase;
      while (phase < 0)
        ++phase;
      int j = phase * WAVETABLE_SIZE;
      out[i] = (*waveform)[j];
    }
  }
};
