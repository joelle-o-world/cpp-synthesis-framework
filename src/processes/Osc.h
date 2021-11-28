#pragma once
#include "../AudioProcess.h"
#include "../wavetables.h"

/**
 * Simple k/a-rate frequency wavetable oscillator.
 */
class Osc : public AudioProcess {
  float phase = 0;
  float rightPhase = 0;

public:
  float frequency = 440;
  Wavetable *waveform = &sineWavetable;

  void setPhase(float l) { phase = rightPhase = l; }

  void flipPhase() { phase = phase + .5; }

  void setPhase(float l, float r) {
    phase = l;
    rightPhase = r;
  }

  Osc() : AudioProcess(1, 1) {}

  void processStatefully() override {
    TypedSignalBuffer &frequency = *inputs[0].buffer;
    TypedSignalBuffer &out = *outputs[0].buffer;
    if (frequency.type == Mono && out.type == Mono)
      process(*frequency.mono, *out.mono);

    else if (frequency.type == Mono && out.type == Stereo)
      process(*frequency.mono, *out.stereo);

    else if (frequency.type == Stereo && out.type == Stereo)
      process(*frequency.stereo, *out.stereo);

    else if (frequency.type == Constant && out.type == Mono)
      process(*frequency.constant, *out.mono);

    else if (frequency.type == Constant && out.type == Stereo)
      process(*frequency.constant, *out.stereo);

    else
      throw "Unexpected io";
  }

  // a-rate monophonic mode
  void process(MonoBuffer &frequency, MonoBuffer &out) {
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

  // a-rate mono-to-stereo mode
  void process(MonoBuffer &frequency, StereoBuffer &out) {
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
  }

  // a-rate stereo mode
  void process(StereoBuffer &frequency, StereoBuffer &out) {
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

  // k-rate mono mode
  void process(float frequency, MonoBuffer &out) {
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

  void process(float frequency, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; i += 2) {
      phase += frequency * sampleInterval;
      while (phase > 1)
        --phase;
      while (phase < 0)
        ++phase;
      int j = phase * WAVETABLE_SIZE;
      out[i] = (*waveform)[j];
      out[i + 1] = out[i];
    }
  }
};
