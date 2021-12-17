#pragma once

#include "../AudioProcess.h"
#include <string>

class Constant : public AudioProcess {
public:
  float value;
  Constant(float value) : AudioProcess(0, 1), value(value) {}

  void process() override {
    float *out = (float *)outputs[0].buffer->stereo;
    for (int i = 0; i < signalChunkSize * 2; ++i) {
      out[i] = value;
    }
  }

  std::string describe() override { return std::to_string(value); }
};
