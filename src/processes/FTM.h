#pragma once

#include <math.h>

#include "../AudioProcess.h"

class FTM : public UnaryOperationProcess {
  void processSample(float &in, float &out) override {
    out = 440.0 * pow(2.0, (in - 69.0) / 12.0);
  }
};

class SemitoneToRatio : public UnaryOperationProcess {
  void processSample(float &in, float &out) { out = pow(2.0, in / 12.0); }
};
