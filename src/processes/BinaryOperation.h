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
    float *a = A();
    float *b = B();
    float *out = OUT();
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a[i], b[i], out[i]);
  }

  inline Reader &a() { return inputs[0]; }
  inline Reader &b() { return inputs[1]; }
  inline Writer &out() { return outputs[0]; }

private:
  inline float *A() { return (float *)a().bufferptr; }
  inline float *B() { return (float *)b().bufferptr; }
  inline float *OUT() { return (float *)out().bufferptr; }
};
