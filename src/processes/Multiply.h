#pragma once

#include "../AudioProcess.h"

/**
 * Multiplies a signal by a k-rate constant.
 */
class Multiply : public AudioProcess {
public:
  float a = 1.0;
  float b = 1.0;

  Multiply() : AudioProcess(2, 1) { }

  void process() override {
    SignalBuffer &out = *outputs[0];

    if (inputs[0] != nullptr) {
      if (inputs[1] != nullptr)
        // a is a-rate, b is a-rate
        process(*inputs[0], *inputs[1], *outputs[0]);

      else
        // a is a-rate, b is k-rate
        process(*inputs[0], b, *outputs[0]);

    } else {
      if (inputs[1] != nullptr)
        // a is k-rate, b is a-rate
        process(a, *inputs[1], *outputs[0]);

      else
        process(a, b, *outputs[0]);
    }
  }

  // Two a-rate signals
  void process(SignalBuffer &a, SignalBuffer &b, SignalBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = a[i] * b[i];
  }

  // a is a-rate, b is k-rate
  void process(SignalBuffer &a, float b, SignalBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = a[i] * b;
  }

  // a is k-rate, b is a-rate
  void process(float a, SignalBuffer &b, SignalBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = a * b[i];
  }

  // two k-rate signals
  void process(float a, float b, SignalBuffer &out) {
    float outval = a * b;
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = outval;
  }
};
