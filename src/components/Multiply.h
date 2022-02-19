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
Multiply &multiply(UntypedWriter &a, AudioProcess &b);
Multiply &multiply(AudioProcess &a, UntypedWriter &b);
Multiply &multiply(UntypedWriter &a, UntypedWriter &b);
Multiply &multiply(float a, UntypedWriter &b);
Multiply &multiply(UntypedWriter &a, float b);

Multiply &operator*(AudioProcess &a, AudioProcess &b);
Multiply &operator*(float a, AudioProcess &b);
Multiply &operator*(AudioProcess &a, float b);
Multiply &operator*(UntypedWriter &a, AudioProcess &b);
Multiply &operator*(AudioProcess &a, UntypedWriter &b);
Multiply &operator*(UntypedWriter &a, UntypedWriter &b);
Multiply &operator*(float a, UntypedWriter &b);
Multiply &operator*(UntypedWriter &a, float b);
