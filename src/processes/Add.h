#pragma once

#include "../AudioProcess.h"
#include "../AudioProcessCoordinator.h"

/**
 * Adds two audio buffers together.
 */
class Add : public AudioProcess {
public:
  float a = 0;
  float b = 0;

  Add(): AudioProcess(2,1) { }

  void process() override {
    if (outputs[0]->type == Stereo) {
      if (inputs[0]->type == Stereo && inputs[1]->type == Stereo)
        process(*inputs[0]->stereo, *inputs[1]->stereo, *outputs[0]->stereo);
      else if (inputs[0]->type == Stereo && inputs[1]->type == Constant)
        process(*inputs[0]->stereo, *inputs[1]->constant, *outputs[0]->stereo);
      else if (inputs[0]->type == Constant && inputs[1]->type == Stereo)
        process(*inputs[0]->constant, *inputs[1]->stereo, *outputs[0]->stereo);
      else if (inputs[0]->type == Constant && inputs[1]->type == Constant)
        process(*inputs[0]->constant, *inputs[1]->stereo, *outputs[0]->stereo);
      else
        throw "unexpected input signal types";
    } else
      throw "output must be stereo";
  }

  // Two a-rate signals
  void process(StereoBuffer &a, StereoBuffer &b, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      out[i] = a[i] + b[i];
  }

  // a is a-rate, b is k-rate
  void process(StereoBuffer &a, float b, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      out[i] = a[i] + b;
  }

  // a is k-rate, b is a-rate
  void process(float a, StereoBuffer &b, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      out[i] = a + b[i];
  }

  // two k-rate signals
  void process(float a, float b, StereoBuffer &out) {
    float outval = a + b;
    for (int i = 0; i < signalChunkSize * 2; ++i)
      out[i] = outval;
  }
};
