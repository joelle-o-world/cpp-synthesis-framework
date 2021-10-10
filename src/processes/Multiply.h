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

    TypedSignalBuffer &a = *inputs[0];
    TypedSignalBuffer &b = *inputs[1];
    TypedSignalBuffer& out = *outputs[0];

    if (out.type == Stereo) {
      if (a.type == Stereo && b.type == Stereo)
        process(*a.stereo, *b.stereo, *out.stereo);

      else if (a.type == Stereo && b.type == Constant)
        process(*a.stereo, *b.constant, *out.stereo);

      else if (a.type == Constant && b.type == Stereo)
        process(*a.constant, *b.stereo, *out.stereo);

      else if (a.type == Constant && b.type == Constant)
        process(*a.constant, *b.constant, *out.stereo);

      else
        throw "unexpected input signal types";

    } else
      throw "output must be stereo";

  }

  // Two a-rate signals
  void process(StereoBuffer &a, StereoBuffer &b, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      out[i] = a[i] * b[i];
  }

  // a is a-rate, b is k-rate
  void process(StereoBuffer &a, float &b, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      out[i] = a[i] * b;
  }

  // a is k-rate, b is a-rate
  void process(float &a, StereoBuffer &b, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      out[i] = a * b[i];
  }

  // two k-rate signals
  void process(float &a, float &b, StereoBuffer &out) {
    float outval = a * b;
    for (int i = 0; i < signalChunkSize * 2; ++i)
      out[i] = outval;
  }
};
