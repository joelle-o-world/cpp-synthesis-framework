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

    float *frequency = FREQUENCY();
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

public:
  std::string describe() override { return "Osc"; }
  Inlet &frequency() { return inputs[0]; }
  Outlet &out() { return outputs[0]; }

private:
  float *FREQUENCY() { return (float *)frequency().bufferptr; }
  float *OUT() { return (float *)out().bufferptr; }
};

Osc &osc(float frequency);
Osc &osc(AudioProcess &frequency);
