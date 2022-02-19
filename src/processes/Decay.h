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
    float *halfLife = HALFLIFE();
    float *out = OUT();
    for (int i = 0; i < signalChunkSize * 2; i += 2) {
      out[i] = level *= halfLifeToScalar(halfLife[i]);
      out[i + 1] = rightLevel *= halfLifeToScalar(halfLife[i + 1]);
    }
  }

  Reader &halfLife() { return inputs[0]; }
  Writer &out() { return outputs[0]; }

private:
  float *HALFLIFE() { return (float *)halfLife().bufferptr; }
  float *OUT() { return (float *)out().bufferptr; }
};

Decay &decay(float halfLife);
Decay &decay(AudioProcess &halfLife);
