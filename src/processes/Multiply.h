#include "../connect.h"
#include "BinaryOperation.h"

/**
 * Multiplies a signal by a k-rate constant.
 */
class Multiply : public BinaryOperation {
public:
  std::string describe() override { return "Multiply"; }

private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a * b;
  }
};

Multiply &multiply(AudioProcess &a, AudioProcess &b);
Multiply &multiply(float a, AudioProcess &b);
Multiply &multiply(AudioProcess &a, float b);
Multiply &multiply(Writer &a, AudioProcess &b);
Multiply &multiply(AudioProcess &a, Writer &b);
Multiply &multiply(Writer &a, Writer &b);
Multiply &multiply(float a, Writer &b);
Multiply &multiply(Writer &a, float b);

Multiply &operator*(AudioProcess &a, AudioProcess &b);
Multiply &operator*(float a, AudioProcess &b);
Multiply &operator*(AudioProcess &a, float b);
Multiply &operator*(Writer &a, AudioProcess &b);
Multiply &operator*(AudioProcess &a, Writer &b);
Multiply &operator*(Writer &a, Writer &b);
Multiply &operator*(float a, Writer &b);
Multiply &operator*(Writer &a, float b);
