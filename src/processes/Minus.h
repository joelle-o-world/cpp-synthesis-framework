#include "UnaryOperation.h"

class Minus : public UnaryOperation {
private:
  inline void processSample(float &in, float &out) { out = -in; }
};
