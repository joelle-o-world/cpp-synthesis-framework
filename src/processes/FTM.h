#pragma once

#include <math.h>

#include "../AudioProcess.h"

class FTM : public AudioProcess {
public:
  FTM() : AudioProcess(1, 1) {}

  void process() override {
    TypedSignalBuffer& a = *inputs[0], out = *outputs[0];
    if (a.type == Stereo && out.type == Stereo)
      process(*a.stereo, *out.stereo);
    else
      throw "Unexpected signal types";
  }

  void process(StereoBuffer &in, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      out[i] = 440.0 * pow(2.0, (in[i] - 69.0) / 12.0);
  }
};

class SemitoneToRatio : public AudioProcess {
public:
  SemitoneToRatio() : AudioProcess(1, 1) {}

  void process() override {
    TypedSignalBuffer& a = *inputs[0], out = *outputs[0];
    if (a.type == Stereo && out.type == Stereo)
      process(*a.stereo, *out.stereo);
    else
      throw "Unexpected signal types";
  }

  void process(StereoBuffer &in, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      out[i] = pow(2.0, in[i] / 12.0);
  }
};
