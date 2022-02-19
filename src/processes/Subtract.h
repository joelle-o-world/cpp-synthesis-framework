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
Subtract &subtract(Writer &a, AudioProcess &b);
Subtract &subtract(AudioProcess &a, Writer &b);
Subtract &subtract(Writer &a, Writer &b);
Subtract &subtract(float a, Writer &b);
Subtract &subtract(Writer &a, float b);

Subtract &operator-(AudioProcess &a, AudioProcess &b);
Subtract &operator-(float a, AudioProcess &b);
Subtract &operator-(AudioProcess &a, float b);
Subtract &operator-(Writer &a, AudioProcess &b);
Subtract &operator-(AudioProcess &a, Writer &b);
Subtract &operator-(Writer &a, Writer &b);
Subtract &operator-(float a, Writer &b);
Subtract &operator-(Writer &a, float b);
