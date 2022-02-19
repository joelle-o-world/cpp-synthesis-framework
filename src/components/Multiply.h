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

Multiply &multiply(Component &a, Component &b);
Multiply &multiply(float a, Component &b);
Multiply &multiply(Component &a, float b);
Multiply &multiply(UntypedWriter &a, Component &b);
Multiply &multiply(Component &a, UntypedWriter &b);
Multiply &multiply(UntypedWriter &a, UntypedWriter &b);
Multiply &multiply(float a, UntypedWriter &b);
Multiply &multiply(UntypedWriter &a, float b);

Multiply &operator*(Component &a, Component &b);
Multiply &operator*(float a, Component &b);
Multiply &operator*(Component &a, float b);
Multiply &operator*(UntypedWriter &a, Component &b);
Multiply &operator*(Component &a, UntypedWriter &b);
Multiply &operator*(UntypedWriter &a, UntypedWriter &b);
Multiply &operator*(float a, UntypedWriter &b);
Multiply &operator*(UntypedWriter &a, float b);
