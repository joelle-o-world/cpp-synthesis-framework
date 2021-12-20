#pragma once
#include "../AudioProcess.h"

class BinaryOperation : public AudioProcess {
public:
  BinaryOperation() : AudioProcess({stereo, stereo}, {stereo}) {}

private:
  virtual inline void processSample(float &a, float &b, float &out) {
    // Base class does nothing
  }

public:
  // Two a-rate signals
  void process() override {
    float *a = (float *)inputs[0].bufferptr;
    float *b = (float *)inputs[1].bufferptr;
    float *out = (float *)outputs[0].bufferptr;
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a[i], b[i], out[i]);
  }
};
