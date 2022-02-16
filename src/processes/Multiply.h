#include "../connect.h"
#include "BinaryOperation.h"

/**
 * Multiplies a signal by a k-rate constant.
 */
class Multiply : public BinaryOperation {
public:
  std::string describe() override { return "Multiply"; }
  inline void processSample(float &a, float &b, float &out) override {
    out = a * b;
  }
};
Multiply &multiply(AudioProcess &a, float b);
Multiply &operator*(AudioProcess &a, float b);
Multiply &multiply(AudioProcess &a, AudioProcess &b);
Multiply &operator*(AudioProcess &a, AudioProcess &b);
