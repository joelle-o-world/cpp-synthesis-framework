#include "../connect.h"
#include "./BinaryOperation.h"

class Divide : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a / b;
  }
};

Divide &divide(AudioProcess &a, AudioProcess &b);
Divide &divide(float a, AudioProcess &b);
Divide &divide(AudioProcess &a, float b);
Divide &divide(Writer &a, AudioProcess &b);
Divide &divide(AudioProcess &a, Writer &b);
Divide &divide(Writer &a, Writer &b);
Divide &divide(float a, Writer &b);
Divide &divide(Writer &a, float b);

Divide &operator/(AudioProcess &a, AudioProcess &b);
Divide &operator/(float a, AudioProcess &b);
Divide &operator/(AudioProcess &a, float b);
Divide &operator/(Writer &a, AudioProcess &b);
Divide &operator/(AudioProcess &a, Writer &b);
Divide &operator/(Writer &a, Writer &b);
Divide &operator/(float a, Writer &b);
Divide &operator/(Writer &a, float b);
