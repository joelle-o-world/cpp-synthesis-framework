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
Divide &divide(UntypedWriter &a, AudioProcess &b);
Divide &divide(AudioProcess &a, UntypedWriter &b);
Divide &divide(UntypedWriter &a, UntypedWriter &b);
Divide &divide(float a, UntypedWriter &b);
Divide &divide(UntypedWriter &a, float b);

Divide &operator/(AudioProcess &a, AudioProcess &b);
Divide &operator/(float a, AudioProcess &b);
Divide &operator/(AudioProcess &a, float b);
Divide &operator/(UntypedWriter &a, AudioProcess &b);
Divide &operator/(AudioProcess &a, UntypedWriter &b);
Divide &operator/(UntypedWriter &a, UntypedWriter &b);
Divide &operator/(float a, UntypedWriter &b);
Divide &operator/(UntypedWriter &a, float b);
