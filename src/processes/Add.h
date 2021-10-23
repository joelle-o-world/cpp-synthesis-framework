#pragma once

#include "../AudioProcess.h"
#include "../AudioProcessCoordinator.h"

/**
 * Adds two audio buffers together.
 */
class Add : public BinaryOperationProcess {
  private:
    void processSample(float &a, float &b, float &out) override {
      out = a + b;
    }
};
