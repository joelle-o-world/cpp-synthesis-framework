#pragma once

#include "../AudioProcess.h"
#include <math.h>
#include <string>

const float logHalf = log(.5);

// TODO: split this class into three classes, Decay and HalfLife and
// RecursiveMultiplier

class Decay : public AudioProcess {
  float level;
  float rightLevel;

  static float halfLifeToScalar(float halfLife) {
    return pow(2, -1 / (sampleRate * halfLife));
  };

public:
  Decay() : AudioProcess(1, 1) {}
  std::string describe() override { return "Decay"; }

  void retrigger() { level = rightLevel = 1.0; }

  void processStatefully() override {
    TypedSignalBuffer &halfLife = *inputs[0].buffer, &out = *outputs[0].buffer;
    if (halfLife.type == Constant && out.type == Mono)
      process(*halfLife.constant, *out.mono);

    else if (halfLife.type == Constant && out.type == Stereo)
      process(*halfLife.constant, *out.stereo);

    else if (halfLife.type == Mono && out.type == Mono)
      process(*halfLife.mono, *out.mono);

    else if (halfLife.type == Mono && out.type == Stereo)
      process(*halfLife.mono, *out.stereo);

    else if (halfLife.type == Stereo && out.type == Stereo)
      process(*halfLife.stereo, *out.stereo);

    else
      throw "Unexpected signal types";
  }

  void process(float halfLife, MonoBuffer &out) {
    float k = halfLifeToScalar(halfLife);
    for (int i = 0; i < signalChunkSize; ++i)
      out[i] = rightLevel = level *= k;
  }

  void process(float halfLife, StereoBuffer &out) {
    process(halfLife, (MonoBuffer &)out);
    stereoify((MonoBuffer &)out, out);
  }

  void process(MonoBuffer &halfLife, MonoBuffer &out) {
    for (int i = 0; i < signalChunkSize; ++i) {
      rightLevel = level *= halfLifeToScalar(halfLife[i]);
      out[i] = level;
    }
  }

  void process(MonoBuffer &halfLife, StereoBuffer &out) {
    process(halfLife, (MonoBuffer &)out);
    stereoify((MonoBuffer &)out, out);
  }

  void process(StereoBuffer &halfLife, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; i += 2) {
      out[i] = level *= halfLifeToScalar(halfLife[i]);
      out[i + 1] = rightLevel *= halfLifeToScalar(halfLife[i + 1]);
    }
  }
};
