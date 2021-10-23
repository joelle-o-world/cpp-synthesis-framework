#pragma once

#include "../AudioProcess.h"

/**
 * Multiplies a signal by a k-rate constant.
 */
class Multiply : public BinaryOperationProcess {
public:

  void processSample (float &a, float &b, float &out) override {
    out = a * b;
  }
};
