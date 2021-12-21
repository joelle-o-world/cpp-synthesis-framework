#pragma once
#include "../AudioProcess.h"
#include "../connect.h"
#include "../wavetables.h"
#include <iostream>
#include <string>

/**
 * Simple k/a-rate frequency wavetable oscillator.
 */
class Osc : public AudioProcess {
  float phase = 0;
  float rightPhase = 0;

public:
  float frequency = 440;
  Wavetable *waveform;

  void setPhase(float l) { phase = rightPhase = l; }

  void flipPhase() { phase = phase + .5; }

  void setPhase(float l, float r) {
    phase = l;
    rightPhase = r;
  }

  Osc() : AudioProcess({stereo}, {stereo}) {}

  // a-rate stereo mode
  void process() override {

    float *frequency = (float *)inputs[0].bufferptr;
    float *out = (float *)outputs[0].bufferptr;

    for (int i = 0; i < signalChunkSize * 2; i += 2) {
      phase += frequency[i] * sampleInterval;
      while (phase > 1)
        --phase;
      while (phase < 0)
        ++phase;

      int j = phase * WAVETABLE_SIZE;
      out[i] = (*waveform)[j];
      out[i + 1] = out[i];
    }
    for (int i = 1; i < signalChunkSize * 2; i += 2) {
      rightPhase += frequency[i] * sampleInterval;
      while (rightPhase > 1)
        --rightPhase;
      while (rightPhase < 0)
        ++rightPhase;

      int j = rightPhase * WAVETABLE_SIZE;
      out[i + 1] = out[i];
    }
  }

  std::string describe() override { return "Osc"; }
};
