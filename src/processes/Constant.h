#pragma once

#include "../AudioProcess.h"
#include <string>

class Constant : public AudioProcess {
public:
  float value;
  Constant(float value) : AudioProcess({}, {stereo}), value(value) {}

  void process() override {
    float *out = OUT();
    for (int i = 0; i < signalChunkSize * 2; ++i) {
      out[i] = value;
    }
  }

  Outlet &out() { return outputs[0]; }

  std::string describe() override { return std::to_string(value); }

private:
  float *OUT() { return (float *)out().bufferptr; }
};
