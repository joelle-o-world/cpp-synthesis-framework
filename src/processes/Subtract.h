#include "./BinaryOperation.h"

class Subtract : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a - b;
  }
};

// TODO: helper functions
// TODO: Operator overloads
