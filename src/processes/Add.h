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

  _Add() {
    inputs = new SignalBuffer*[2];
    outputs = new SignalBuffer*[1];
  }

  void process() override {

    SignalBuffer& out = *outputs[0];

    if(inputs[0] != nullptr && inputs[1] != nullptr) {
      // Two a-rate signals
      SignalBuffer& a = *inputs[0];
      SignalBuffer& b = *inputs[1];
      for(int i=0; i < signalChunkSize; ++i) 
        out[i] = a[i] + b[i];

    } else if(inputs[0] != nullptr) {
      // a is a-rate, b is k-rate
      SignalBuffer& a = *inputs[0];
      for(int i=0; i < signalChunkSize; ++i)
        out[i] = a[i] + b;

    } else if(inputs[1] != nullptr) {
      // a is k-rate, b is a-rate
      SignalBuffer& b = *inputs[1];
      for(int i=0; i < signalChunkSize; ++i)
        out[i] = a + b[i];

    } else {
      // two k-rate signals. Weird edge case
      float outval = a + b;
      for(int i=0; i < signalChunkSize; ++i)
        out[i] = outval;
    }
  }
};
