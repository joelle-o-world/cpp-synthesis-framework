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
Multiply &multiply(Outlet &a, AudioProcess &b);
Multiply &multiply(AudioProcess &a, Outlet &b);
Multiply &multiply(Outlet &a, Outlet &b);
Multiply &multiply(float a, Outlet &b);
Multiply &multiply(Outlet &a, float b);

Multiply &operator*(AudioProcess &a, AudioProcess &b);
Multiply &operator*(float a, AudioProcess &b);
Multiply &operator*(AudioProcess &a, float b);
Multiply &operator*(Outlet &a, AudioProcess &b);
Multiply &operator*(AudioProcess &a, Outlet &b);
Multiply &operator*(Outlet &a, Outlet &b);
Multiply &operator*(float a, Outlet &b);
Multiply &operator*(Outlet &a, float b);
