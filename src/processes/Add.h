#pragma once

#include "../AudioProcess.h"
#include "../AudioProcessCoordinator.h"

/**
 * Adds two audio buffers together.
 */
class _Add : public AudioProcess {
public:
  float a = 0;
  float b = 0;

  _Add(): AudioProcess(2,1) {
    inputs = new SignalBuffer*[2];
    outputs = new SignalBuffer*[1];
  }

  void process() override {
    if (inputs[0] != nullptr && inputs[1] != nullptr)
      process(*inputs[0], *inputs[1], *outputs[0]);
    else if (inputs[0] != nullptr)
      process(*inputs[0], b, *outputs[0]);
    else if (inputs[1] != nullptr)
      process(*inputs[0], b, *outputs[0]);
    else
      process(a, b, *outputs[0]);
  }

  // Two a-rate signals
  void process(SignalBuffer &a, SignalBuffer &b, SignalBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = a[i] + b[i];
  }

  // a is a-rate, b is k-rate
  void process(SignalBuffer &a, float b, SignalBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = a[i] + b;
  }

  // a is k-rate, b is a-rate
  void process(float a, SignalBuffer &b, SignalBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = a + b[i];
  }

  // two k-rate signals
  void process(float a, float b, SignalBuffer &out) {
    float outval = a + b;
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = outval;
  }
};
