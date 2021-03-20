#pragma once

#include "../AudioProcess.h"
#include "../AudioProcessCoordinator.h"

/**
 * Adds two audio buffers together.
 */
class _Add : public AudioProcess {
public:
  _Add() {
    inputs = new SignalBuffer*[2];
    outputs = new SignalBuffer*[1];
  }

  void process() override {
    SignalBuffer& a = *inputs[0];
    SignalBuffer& b = *inputs[1];
    SignalBuffer& out = *outputs[0];
    for(int i=0; i < signalChunkSize; ++i) 
      out[i] = a[i] + b[i];
  }
};
