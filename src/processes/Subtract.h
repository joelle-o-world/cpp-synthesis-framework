#include "../connect.h"
#include "./BinaryOperation.h"

class Subtract : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a - b;
  }
};

Subtract &subtract(AudioProcess &a, AudioProcess &b);
Subtract &subtract(float a, AudioProcess &b);
Subtract &subtract(AudioProcess &a, float b);
Subtract &subtract(UntypedWriter &a, AudioProcess &b);
Subtract &subtract(AudioProcess &a, UntypedWriter &b);
Subtract &subtract(UntypedWriter &a, UntypedWriter &b);
Subtract &subtract(float a, UntypedWriter &b);
Subtract &subtract(UntypedWriter &a, float b);

Subtract &operator-(AudioProcess &a, AudioProcess &b);
Subtract &operator-(float a, AudioProcess &b);
Subtract &operator-(AudioProcess &a, float b);
Subtract &operator-(UntypedWriter &a, AudioProcess &b);
Subtract &operator-(AudioProcess &a, UntypedWriter &b);
Subtract &operator-(UntypedWriter &a, UntypedWriter &b);
Subtract &operator-(float a, UntypedWriter &b);
Subtract &operator-(UntypedWriter &a, float b);
