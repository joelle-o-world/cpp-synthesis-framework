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
// TODO: More addition overloads
Add &add(AudioProcess &a, AudioProcess &b);
Add &operator+(AudioProcess &a, AudioProcess &b);
