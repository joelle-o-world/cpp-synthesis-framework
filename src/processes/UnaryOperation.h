#pragma once
#include "../AudioProcess.h"

class UnaryOperation : public AudioProcess {
public:
  UnaryOperation() : AudioProcess({stereo}, {stereo}) {}

public:
  virtual inline void processSample(float &in, float &out) {
    throw "No override defined";
  }

  void process() {
    float *in = (float *)inputs[0].bufferptr;
    float *out = (float *)outputs[0].bufferptr;

    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(out[i], in[i]);
  }

public:
  Reader &in() { return inputs[0]; }
  Outlet &out() { return outputs[0]; }

private:
  float *IN() { return (float *)in().bufferptr; }
  float *OUT() { return (float *)out().bufferptr; }
};
