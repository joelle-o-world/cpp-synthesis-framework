#pragma once

#include "../AudioProcess.h"
#include <math.h>
#include <string>

const float logHalf = log(.5);

// TODO: split this class into three classes, Decay and HalfLife and
// RecursiveMultiplier

class Decay : public AudioProcess {
  // internal state
  float level;
  float rightLevel;

  static float halfLifeToScalar(float halfLife) {
    return pow(2, -1 / (sampleRate * halfLife));
  };

public:
  Decay() : AudioProcess({stereo}, {stereo}) { retrigger(); }
  std::string describe() override { return "Decay"; }

  void retrigger() { level = rightLevel = 1.0; }

  void process() override {
    auto HALFLIFE = HalfLife().data();
    float *out = Out().data();
    for (int i = 0; i < signalChunkSize * 2; i += 2) {
      out[i] = level *= halfLifeToScalar(HALFLIFE[i]);
      out[i + 1] = rightLevel *= halfLifeToScalar(HALFLIFE[i + 1]);
    }
  }

  Reader<StereoBuffer> &HalfLife() { return (Reader<StereoBuffer> &)inputs[0]; }
  Writer<StereoBuffer> &Out() { return (Writer<StereoBuffer> &)outputs[0]; }
};

Decay &decay(float halfLife);
Decay &decay(AudioProcess &halfLife);
