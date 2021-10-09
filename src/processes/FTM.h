#pragma once

#include <math.h>

#include "../AudioProcess.h"

class FTM : public AudioProcess {
public:
  FTM() : AudioProcess(1, 1) {}

  void process() override { process(*inputs[0], *outputs[0]); }

  void process(SignalBuffer &in, SignalBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = 440.0 * pow(2.0, (in[i] - 69.0) / 12.0);
  }
};

class SemitoneToRatio : public AudioProcess {
public:
  SemitoneToRatio() : AudioProcess(1, 1) {}

  void process() override { process(*inputs[0], *outputs[0]); }

  void process(SignalBuffer &in, SignalBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = pow(2.0, in[i] / 12.0);
  }
};
