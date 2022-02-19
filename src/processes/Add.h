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
Add &add(Writer &a, AudioProcess &b);
Add &add(AudioProcess &a, Writer &b);
Add &add(Writer &a, Writer &b);
Add &add(float a, Writer &b);
Add &add(Writer &a, float b);

Add &operator+(AudioProcess &a, AudioProcess &b);
Add &operator+(float a, AudioProcess &b);
Add &operator+(AudioProcess &a, float b);
Add &operator+(Writer &a, AudioProcess &b);
Add &operator+(AudioProcess &a, Writer &b);
Add &operator+(Writer &a, Writer &b);
Add &operator+(float a, Writer &b);
Add &operator+(Writer &a, float b);
