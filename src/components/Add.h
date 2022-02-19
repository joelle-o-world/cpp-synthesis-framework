#include "../connect.h"
#include "./BinaryOperation.h"

/**
 * Adds two audio buffers together.
 */
class Add : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a + b;
  }
};

Add &add(AudioProcess &a, AudioProcess &b);
Add &add(float a, AudioProcess &b);
Add &add(AudioProcess &a, float b);
Add &add(UntypedWriter &a, AudioProcess &b);
Add &add(AudioProcess &a, UntypedWriter &b);
Add &add(UntypedWriter &a, UntypedWriter &b);
Add &add(float a, UntypedWriter &b);
Add &add(UntypedWriter &a, float b);

Add &operator+(AudioProcess &a, AudioProcess &b);
Add &operator+(float a, AudioProcess &b);
Add &operator+(AudioProcess &a, float b);
Add &operator+(UntypedWriter &a, AudioProcess &b);
Add &operator+(AudioProcess &a, UntypedWriter &b);
Add &operator+(UntypedWriter &a, UntypedWriter &b);
Add &operator+(float a, UntypedWriter &b);
Add &operator+(UntypedWriter &a, float b);
