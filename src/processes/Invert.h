#include "UnaryOperation.h"

class Invert : public UnaryOperation {
private:
  inline void processSample(float &in, float &out) { out = 1.0 / in; }
};
